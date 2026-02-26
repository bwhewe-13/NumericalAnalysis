from setuptools import find_packages, setup

setup(
    name="numeric",
    description="""Implementing algorithms from 'Numerical Analysis' by
    Richard L. Burden and J. Douglas Faires (9th Edition) in
    C++ with Python bindings.""",
    version="0.1.0",
    author="Ben Whewell",
    author_email="ben.whewell@pm.me",
    url="https://github.com/bwhewe-13/NumericalAnalysis",
    packages=find_packages(),
    include_package_data=True,
    install_requires=[
        "numpy",
    ],
    extras_require={
        "dev": [
            "pytest>=6.0",
            "pytest-cov",
            "black",
            "isort",
            "flake8",
            "pre-commit",
        ]
    },
)
