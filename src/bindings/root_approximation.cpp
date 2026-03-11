#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

#include <stdexcept>
#include <vector>

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

    /**
     * @brief Bind the Secant root approximation function to Python.
     */
    m.def(
        "secant_method",
        &secant_method,
        R"pbdoc(
secant_method(func, x0, x1, max_iters=100, tol=1e-8)

Approximate a root using the secant method from initial approximations x0 and x1.

Parameters
----------
func : Callable[[float], float]
x0 : float
x1 : float
max_iters : int, optional
tol : float, optional

Returns
-------
float
)pbdoc",
        py::arg("func"),
        py::arg("x0"),
        py::arg("x1"),
        py::arg("max_iters") = 100,
        py::arg("tol") = 1e-8
    );

    /**
     * @brief Bind the false position root approximation function to Python.
     */
    m.def(
        "false_position",
        &false_position,
        R"pbdoc(
false_position(func, x0, x1, max_iters=100, tol=1e-8)

Approximate a root using the false position method from initial approximations x0 and x1.

Parameters
----------
func : Callable[[float], float]
x0 : float
x1 : float
max_iters : int, optional
tol : float, optional

Returns
-------
float
)pbdoc",
        py::arg("func"),
        py::arg("x0"),
        py::arg("x1"),
        py::arg("max_iters") = 100,
        py::arg("tol") = 1e-8
    );

    /**
     * @brief Bind the Steffensen's method root approximation function to Python.
     */
    m.def(
        "steffensen_method",
        &steffensen_method,
        R"pbdoc(
steffensen_method(func, x0, max_iters=100, tol=1e-8)

Approximate a root using Steffensen's method from initial approximation x0.

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
     * @brief Bind Muller's root approximation function to Python.
     */
    m.def(
        "mullers",
        &mullers,
        R"pbdoc(
mullers(func, p0, p1, p2, max_iters=100, tol=1e-8)

Approximate a root using Muller's method from three initial approximations.

Parameters
----------
func : Callable[[float], float]
p0 : float
p1 : float
p2 : float
max_iters : int, optional
tol : float, optional

Returns
-------
float
)pbdoc",
        py::arg("func"),
        py::arg("p0"),
        py::arg("p1"),
        py::arg("p2"),
        py::arg("max_iters") = 100,
        py::arg("tol") = 1e-8
    );

    /**
     * @brief Bind Horner's polynomial and derivative evaluation to Python.
     */
    m.def(
        "horners",
        [](const std::vector<double>& coefs, double x0) {
            if (coefs.empty()) {
                throw std::invalid_argument("coefs must have at least one coefficient");
            }
            return horners(static_cast<int>(coefs.size()) - 1, coefs.data(), x0);
        },
        R"pbdoc(
horners(coefs, x0)

Evaluate polynomial value and derivative at x0 using Horner's method.

Parameters
----------
coefs : Sequence[float]
    Polynomial coefficients from highest to lowest degree.
x0 : float

Returns
-------
tuple[float, float]
    (P(x0), P'(x0))
)pbdoc",
        py::arg("coefs"),
        py::arg("x0")
    );
}
