#pragma once
#include <functional>

/**
 * @brief Approximate a root of f(x) = 0 using the bisection method.
 *
 * This implements Algorithm 2.1 from Burden and Faires (9th Edition)
 * on an interval [a, b] where the function changes sign.
 *
 * @param func Continuous function f(x).
 * @param a Left endpoint of the interval.
 * @param b Right endpoint of the interval.
 * @param MAX_ITERS Maximum number of iterations.
 * @param TOL Convergence tolerance for half-interval width.
 * @return Approximate root within the interval.
 */
double bisection(
    const std::function<double(double)>& func, 
    double a, 
    double b, 
    int MAX_ITERS,
    double TOL
);