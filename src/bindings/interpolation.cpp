#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "numeric/interpolation.hpp"

namespace py = pybind11;

/**
 * @brief Define Python bindings for interpolation algorithms.
 *
 * Exposes the C++ Neville and Newton divided-difference implementations as
 * `numeric.interpolation.neville` and `numeric.interpolation.newton`.
 */
PYBIND11_MODULE(interpolation, m) {
    m.doc() = "Interpolation algorithms from Numerical Analysis (Chapter 3)";

    /**
     * @brief Bind Neville's iterated interpolation to Python.
     */
    m.def(
        "neville",
        &neville,
        R"pbdoc(
neville(x, xn, fn)

Evaluate the interpolating polynomial at x using Neville's iterated interpolation.

Parameters
----------
x : float
    The point at which to evaluate the interpolating polynomial.
xn : Sequence[float]
    The x-values of the known data points.
fn : Sequence[float]
    The corresponding y-values of the known data points.

Returns
-------
float
    The value of the interpolating polynomial at x.
)pbdoc",
        py::arg("x"),
        py::arg("xn"),
        py::arg("fn")
    );

    /**
     * @brief Bind Newton's divided-difference coefficients to Python.
     */
    m.def(
        "newton",
        &newton,
        R"pbdoc(
newton(xn, fn)

Compute the Newton divided-difference coefficients for the interpolating polynomial.

Parameters
----------
xn : Sequence[float]
    The x-values of the known data points.
fn : Sequence[float]
    The corresponding y-values of the known data points.

Returns
-------
list[float]
    The divided-difference coefficients [F[0][0], F[1][1], ..., F[n][n]].
)pbdoc",
        py::arg("xn"),
        py::arg("fn")
    );
}
