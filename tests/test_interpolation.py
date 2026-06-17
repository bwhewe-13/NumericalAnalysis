import numeric
import pytest


@pytest.mark.parametrize(
    "function_name",
    [
        "neville",
        "newton",
    ],
)
def test_binding_docstrings_include_numpy_sections(function_name):
    doc = getattr(numeric.interpolation, function_name).__doc__
    assert doc is not None
    assert "Parameters" in doc
    assert "Returns" in doc


@pytest.mark.smoke
def test_neville_01():
    xn = [1.0, 2.0, 4.0]
    fn = [1.0, 4.0, 16.0]  # f(x) = x^2
    approx = numeric.interpolation.neville(3.0, xn, fn)
    reference = 9.0
    assert abs(approx - reference) < 1e-8


def test_neville_02():
    xn = [0.0, 1.0, 2.0, 3.0]
    fn = [-10.0, -5.0, 14.0, 53.0]  # f(x) = x^3 + 4x^2 - 10
    approx = numeric.interpolation.neville(1.5, xn, fn)
    reference = 2.375
    assert abs(approx - reference) < 1e-8


@pytest.mark.smoke
def test_newton_01():
    xn = [1.0, 2.0, 4.0]
    fn = [1.0, 4.0, 16.0]  # f(x) = x^2
    coefs = numeric.interpolation.newton(xn, fn)
    reference = [1.0, 3.0, 1.0]
    assert len(coefs) == len(reference)
    for value, expected in zip(coefs, reference):
        assert abs(value - expected) < 1e-8


def test_newton_02():
    xn = [1.0, 2.0, 3.0]
    fn = [-5.0, 14.0, 53.0]  # f(x) = x^3 + 4x^2 - 10
    coefs = numeric.interpolation.newton(xn, fn)
    reference = [-5.0, 19.0, 10.0]
    assert len(coefs) == len(reference)
    for value, expected in zip(coefs, reference):
        assert abs(value - expected) < 1e-8
