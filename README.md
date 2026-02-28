# NumericalAnalysis

[![Python Tests](https://github.com/bwhewe-13/NumericalAnalysis/actions/workflows/python-tests.yml/badge.svg)](https://github.com/bwhewe-13/NumericalAnalysis/actions/workflows/python-tests.yml)
[![C++ Tests](https://github.com/bwhewe-13/NumericalAnalysis/actions/workflows/cpp-tests.yml/badge.svg)](https://github.com/bwhewe-13/NumericalAnalysis/actions/workflows/cpp-tests.yml)
[![Quality Gates](https://github.com/bwhewe-13/NumericalAnalysis/actions/workflows/quality-gates.yml/badge.svg)](https://github.com/bwhewe-13/NumericalAnalysis/actions/workflows/quality-gates.yml)
[![codecov](https://codecov.io/gh/bwhewe-13/NumericalAnalysis/graph/badge.svg)](https://codecov.io/gh/bwhewe-13/NumericalAnalysis)
![License](https://img.shields.io/github/license/bwhewe-13/NumericalAnalysis)
![Python](https://img.shields.io/badge/python-3.9%20%7C%203.10%20%7C%203.11%20%7C%203.12%20%7C%203.13-blue)

This project implements numerical methods from *Numerical Analysis* (9th Edition) by Richard L. Burden and J. Douglas Faires.

The core algorithms are written in C++, with Python bindings provided for use from Python.

## Installation

Install the package:

`pip install .`

Install in editable mode with development tools:

`pip install -e ".[dev]"`

## Development requirement

All C++ function declarations and definitions must use Doxygen-style comments (`/** ... */`) directly above each function.

Git pushes are enforced through a `pre-push` hook that runs `pre-commit` checks:

- `black`
- `isort`
- `flake8`
- `pytest-cov`
- `doxygen-check` (`scripts/check_doxygen.py`)
- `catch2-ctest` (C++ Catch2 tests via CTest)

Install the development tools with:

`pip install -e ".[dev]"`

Ensure git uses the repository hooks path:

`git config core.hooksPath .githooks`
