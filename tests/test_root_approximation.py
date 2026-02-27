import numeric
import pytest


@pytest.mark.smoke
def test_bisection_01():
    def function(x):
        return 2 * x - 1

    approx = numeric.root_approximation.bisection(function, -1, 1)
    reference = 0.5
    assert abs(approx - reference) < 1e-8


def test_bisection_02():
    def function(x):
        return x**3 + 4 * x**2 - 10

    approx = numeric.root_approximation.bisection(function, 1, 2)
    reference = 1.36523001341410
    assert abs(approx - reference) < 1e-8


@pytest.mark.smoke
def test_fixed_point_01():
    def function(x):
        return 0.5 * (10 - x**3) ** (0.5)

    approx = numeric.root_approximation.fixed_point(function, 1.5)
    reference = function(approx)
    assert abs(approx - reference) < 1e-8


def test_fixed_point_02():
    def function(x):
        return (x + 2 / x) / 2

    approx = numeric.root_approximation.fixed_point(function, 1.0)
    reference = 1.41421356237310
    assert abs(approx - reference) < 1e-8
