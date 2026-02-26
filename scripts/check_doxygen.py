#!/usr/bin/env python3
from __future__ import annotations

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SCAN_DIRS = [ROOT / "include", ROOT / "src"]
SUFFIXES = {".hpp", ".h", ".cpp", ".cc", ".cxx"}
CONTROL_KEYWORDS = {"if", "for", "while", "switch", "catch"}
FUNCTION_START_RE = re.compile(r"^(?:[\w:<>~*&]+\s+)+[A-Za-z_]\w*\s*\(")


def iter_cpp_files() -> list[Path]:
    files: list[Path] = []
    for scan_dir in SCAN_DIRS:
        if not scan_dir.exists():
            continue
        for path in scan_dir.rglob("*"):
            if path.is_file() and path.suffix in SUFFIXES:
                files.append(path)
    return sorted(files)


def is_candidate_signature(signature: str) -> bool:
    text = signature.strip()
    if not text:
        return False
    if text.startswith("#"):
        return False
    if text.startswith("PYBIND11_MODULE"):
        return True
    if "(" not in text or ")" not in text:
        return False
    if any(
        text.startswith(keyword + " ") or text.startswith(keyword + "(")
        for keyword in CONTROL_KEYWORDS
    ):
        return False
    if text.endswith(";") and "typedef" in text:
        return False
    if "=" in text and text.endswith(";"):
        return False
    return True


def has_doxygen_comment(lines: list[str], signature_start_index: int) -> bool:
    idx = signature_start_index - 1

    while idx >= 0 and not lines[idx].strip():
        idx -= 1

    if idx < 0 or lines[idx].strip() != "*/":
        return False

    while idx >= 0:
        stripped = lines[idx].strip()
        if stripped.startswith("/**"):
            return True
        if not stripped.startswith("*") and stripped != "*/":
            return False
        idx -= 1

    return False


def check_file(path: Path) -> list[tuple[int, str]]:
    issues: list[tuple[int, str]] = []
    lines = path.read_text(encoding="utf-8").splitlines()

    start = None
    buffer: list[str] = []

    for i, line in enumerate(lines):
        stripped = line.strip()

        if start is None:
            if (
                stripped.startswith("//")
                or stripped.startswith("*")
                or stripped.startswith("/*")
            ):
                continue
            if stripped.startswith("PYBIND11_MODULE("):
                start = i
                buffer = [line]
                continue
            if FUNCTION_START_RE.match(stripped):
                start = i
                buffer = [line]
            continue

        buffer.append(line)

        joined = " ".join(piece.strip() for piece in buffer)
        if ")" not in joined:
            continue

        if not any(token in joined for token in ["{", ";"]):
            continue

        if is_candidate_signature(joined):
            if not has_doxygen_comment(lines, start):
                issues.append((start + 1, joined[:120]))

        start = None
        buffer = []

    return issues


def main() -> int:
    all_issues: list[tuple[Path, int, str]] = []

    for file_path in iter_cpp_files():
        for line_no, signature in check_file(file_path):
            rel = file_path.relative_to(ROOT)
            all_issues.append((rel, line_no, signature))

    if all_issues:
        print(
            "Doxygen check failed. Add a /** ... */ comment directly above each "
            "C++ function declaration/definition."
        )
        for rel, line_no, signature in all_issues:
            print(f" - {rel}:{line_no} -> {signature}")
        return 1

    print("Doxygen check passed.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
