#include <pybind11/pybind11.h>
#include <pybind11/functional.h>   // IMPORTANT
#include "numeric/root_approximation.hpp"

namespace py = pybind11;

/**
 * @brief Define Python bindings for root approximation algorithms.
 *
 * Exposes the C++ bisection implementation as
 * `numeric.root_approximation.bisection`.
 */
PYBIND11_MODULE(root_approximation, m) {
    m.doc() = "Bisection using std::function";

    /**
     * @brief Bind the bisection function to Python.
     */
    m.def(
        "bisection",
        &bisection,
        py::arg("func"),
        py::arg("a"),
        py::arg("b"),
        py::arg("max_iters") = 100,
        py::arg("tol") = 1e-8
    );
}