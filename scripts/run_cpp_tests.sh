#!/usr/bin/env bash
set -euo pipefail

repo_root="$(git rev-parse --show-toplevel)"
build_dir="$repo_root/build/precommit-cpp-tests"

cmake_args=(
  -S "$repo_root"
  -B "$build_dir"
  -DBUILD_TESTING=ON
  -DBUILD_PYTHON_BINDINGS=OFF
)

if command -v ninja >/dev/null 2>&1; then
  cmake_args+=( -G Ninja )
else
  cmake_args+=( -G "Unix Makefiles" )
fi

cmake "${cmake_args[@]}"
cmake --build "$build_dir" --target test_root_approximation_cpp
ctest --test-dir "$build_dir" --output-on-failure -R test_root_approximation_cpp
