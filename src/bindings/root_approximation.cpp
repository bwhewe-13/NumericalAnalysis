#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include "numeric/root_approximation.hpp"

namespace py = pybind11;

/**
 * @brief Define Python bindings for root approximation algorithms.
 *
 * Exposes the C++ bisection implementation as
 * `numeric.root_approximation.bisection`.
 */
PYBIND11_MODULE(root_approximation, m) {
    m.doc() = "Root approximation algorithms using std::function";

    /**
     * @brief Bind the bisection function to Python.
     */
    m.def(
        "bisection",
        &bisection,
        R"pbdoc(
bisection(func, a, b, max_iters=100, tol=1e-8)

Approximate a root on [a, b] using the bisection method.

Parameters
----------
func : Callable[[float], float]
a, b : float
max_iters : int, optional
tol : float, optional

Returns
-------
float
)pbdoc",
        py::arg("func"),
        py::arg("a"),
        py::arg("b"),
        py::arg("max_iters") = 100,
        py::arg("tol") = 1e-8
    );

    /**
     * @brief Bind the fixed point iteration function to Python.
     */
    m.def(
        "fixed_point",
        &fixed_point,
        R"pbdoc(
fixed_point(func, x0, max_iters=100, tol=1e-8)

Approximate a fixed point x = f(x) from initial guess x0.

Parameters
----------
func : Callable[[float], float]
x0 : float
max_iters : int, optional
tol : float, optional

Returns
-------
float
)pbdoc",
        py::arg("func"),
        py::arg("x0"),
        py::arg("max_iters") = 100,
        py::arg("tol") = 1e-8
    );

    /**
     * @brief Bind the first derivative approximation function to Python.
     */
    m.def(
        "first_derivative",
        &first_derivative,
        R"pbdoc(
first_derivative(func, x, epsilon=1e-3)

Approximate f'(x) using a centered finite difference.

Parameters
----------
func : Callable[[float], float]
x : float
epsilon : float, optional

Returns
-------
float
)pbdoc",
        py::arg("func"),
        py::arg("x"),
        py::arg("epsilon") = 1e-3
    );

    /**
     * @brief Bind the Newton-Raphson root approximation function to Python.
     */
    m.def(
        "newton_method",
        &newton_method,
        R"pbdoc(
newton_method(func, x0, max_iters=100, tol=1e-8)

Approximate a root using Newton-Raphson iteration from x0.

Parameters
----------
func : Callable[[float], float]
x0 : float
max_iters : int, optional
tol : float, optional

Returns
-------
float
)pbdoc",
        py::arg("func"),
        py::arg("x0"),
        py::arg("max_iters") = 100,
        py::arg("tol") = 1e-8
    );
}
