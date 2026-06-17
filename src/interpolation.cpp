#include <cmath>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include "numeric/interpolation.hpp"

/**
 * @brief Evaluate the interpolating polynomial P on the n + 1 distinct numbers 
 * x0, ..., xn at the number x for the function f using Neville's iterated 
 * interpolation. Algorithm 3.1 in "Numerical Analysis". 
 *
 * @param x The point at which to evaluate the interpolating polynomial.
 * @param xn The x-values of the known data points.
 * @param fn The corresponding y-values of the known data points.
 * @return The value of the interpolating polynomial at x.
 */
double neville(
    double x,
    const std::vector<double>& xn,
    const std::vector<double>& fn
){
    auto Q = std::vector<std::vector<double>>(xn.size(), std::vector<double>(xn.size(), 0.0));

    for (size_t i = 0; i < xn.size(); ++i) {
        Q[i][0] = fn[i];
    }

    // Step 1
    for (size_t j = 1; j < xn.size(); ++j) {
        for (size_t i = j; i < xn.size(); ++i) {
            Q[i][j] = ((xn[i] - x) * Q[i - 1][j - 1] - (xn[i - j] - x) * Q[i][j - 1]) / (xn[i] - xn[i - j]);
        }
    }

    // Step 2
    return Q[xn.size() - 1][xn.size() - 1];
}

/**
 * @brief Obtain the divided-difference coefficients of the interpolatory
 * polynomial P on the (n+1) distinct numbers x0, x1, ..., xn for the function
 * f using Newton's divided-difference formula. Algorithm 3.2 in "Numerical Analysis".
 *
 * @param xn The x-values of the known data points.
 * @param fn The corresponding y-values of the known data points.
 * @return The divided-difference coefficients {F[0][0], F[1][1], ..., F[n][n]},
 * i.e. the diagonal of the divided-difference table.
 */
std::vector<double> newton(
    const std::vector<double>& xn,
    const std::vector<double>& fn
){
    auto F = std::vector<std::vector<double>>(xn.size(), std::vector<double>(xn.size(), 0.0));

    for (size_t i = 0; i < xn.size(); ++i) {
        F[i][0] = fn[i];
    }

    // Step 1
    for (size_t j = 1; j < xn.size(); ++j) {
        for (size_t i = j; i < xn.size(); ++i) {
            F[i][j] = (F[i][j - 1] - F[i - 1][j - 1]) / (xn[i] - xn[i - j]);
        }
    }

    // Step 2: collect the diagonal coefficients F[i][i].
    auto coefs = std::vector<double>(xn.size());
    for (size_t i = 0; i < xn.size(); ++i) {
        coefs[i] = F[i][i];
    }
    return coefs;
}
