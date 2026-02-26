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
