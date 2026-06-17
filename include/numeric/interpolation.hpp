#pragma once
#include <functional>
#include <tuple>
#include <vector>

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
);

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
);