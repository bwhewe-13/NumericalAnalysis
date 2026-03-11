import math

import numeric
import pytest


@pytest.mark.parametrize(
    "function_name",
    [
        "bisection",
        "fixed_point",
        "first_derivative",
        "newton_method",
        "secant_method",
        "mullers",
        "horners",
    ],
)
def test_binding_docstrings_include_numpy_sections(function_name):
    doc = getattr(numeric.root_approximation, function_name).__doc__
    assert doc is not None
    assert "Parameters" in doc
    assert "Returns" in doc


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


@pytest.mark.smoke
def test_first_derivative_01():
    def function(x):
        return x**2

    approx = numeric.root_approximation.first_derivative(function, 2.0)
    reference = 4.0
    assert abs(approx - reference) < 1e-3


@pytest.mark.smoke
def test_newton_method_01():
    def function(x):
        return x**2 - 2

    approx = numeric.root_approximation.newton_method(function, 1.0)
    reference = 1.41421356237310
    assert abs(approx - reference) < 1e-8


@pytest.mark.smoke
def test_secant_method_01():
    def function(x):
        return math.cos(x) - x

    p0 = 0.5
    p1 = 0.25 * math.pi
    approx = numeric.root_approximation.secant_method(function, p0, p1)
    reference = 0.73908513321516064166
    assert abs(approx - reference) < 1e-8


def test_secant_method_02():
    def function(x):
        return x**3 + 4 * x**2 - 10

    p0 = 1.0
    p1 = 2.0
    approx = numeric.root_approximation.secant_method(function, p0, p1)
    reference = 1.36523001341410
    assert abs(approx - reference) < 1e-8


@pytest.mark.smoke
def test_false_position_01():
    def function(x):
        return math.cos(x) - x

    p0 = 0.5
    p1 = 0.25 * math.pi
    approx = numeric.root_approximation.false_position(function, p0, p1)
    reference = 0.73908513321516064166
    assert abs(approx - reference) < 1e-8


def test_false_position_02():
    def function(x):
        return x**3 + 4 * x**2 - 10

    approx = numeric.root_approximation.false_position(function, 1, 2)
    reference = 1.36523001341410
    assert abs(approx - reference) < 1e-8


@pytest.mark.smoke
def test_steffensen_method_01():
    def function(x):
        return (10 / (x + 4)) ** (0.5)

    approx = numeric.root_approximation.steffensen_method(function, 1.5)
    reference = 1.36523001341409684576
    assert abs(approx - reference) < 1e-8


def test_steffensen_method_02():
    def function(x):
        return 0.5 * (10 - x**3) ** (0.5)

    approx = numeric.root_approximation.steffensen_method(function, 1.5)
    reference = function(approx)
    assert abs(approx - reference) < 1e-8


@pytest.mark.smoke
def test_horners_01():
    an = [2, 0, -3, 3, -4]
    x0 = -2
    poly_val, deriv_val = numeric.root_approximation.horners(an, x0)

    assert abs(poly_val - 10.0) < 1e-12
    assert abs(deriv_val - -49.0) < 1e-12


def test_horners_02():
    coefs = [2.0, -6.0, 2.0, -1.0]
    poly_val, deriv_val = numeric.root_approximation.horners(coefs, 3.0)

    assert abs(poly_val - 5.0) < 1e-12
    assert abs(deriv_val - 20.0) < 1e-12


def test_horners_03_error_empty_coefficients():
    with pytest.raises(ValueError, match="coefs need at least one coefficient"):
        numeric.root_approximation.horners([], 1.0)


@pytest.mark.smoke
def test_mullers_01():
    def function(x):
        return x**3 + 4 * x**2 - 10

    approx = numeric.root_approximation.mullers(function, 1.0, 1.5, 2.0)
    reference = 1.36523001341410
    assert abs(approx - reference) < 1e-8


def test_mullers_02_error_duplicate_initial_points():
    def function(x):
        return x**2 - 2

    with pytest.raises(ValueError, match="distinct initial approximations"):
        numeric.root_approximation.mullers(function, 1.0, 1.0, 2.0)
