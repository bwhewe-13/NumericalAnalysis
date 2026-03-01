#pragma once
#include <functional>

/**
 * @brief Approximate a root of f(x) = 0 using the bisection method. Algorithm
 * 2.1 in "Numerical Analysis".
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

/**
 * @brief Approximate a root of f(x) = 0 using the fixed point iteration method.
 * Algorithm 2.2 in "Numerical Analysis".
 *
 * @param func Continuous function f(x).
 * @param x0 Initial approximation.
 * @param MAX_ITERS Maximum number of iterations.
 * @param TOL Convergence tolerance.
 * @return Approximate root x such that f(x) is near zero.
 */
double fixed_point(
    const std::function<double(double)>& func,
    double x0,
    int MAX_ITERS,
    double TOL
);

/**
 * @brief First Derivative Point Approximation
 *
 * @param func Continuous function f(x).
 * @param x Initial approximation.
 * @param epsilon Small perturbation for numerical derivative.
 * @return Approximate first derivative of f at x.
 */
double first_derivative(
    const std::function<double(double)>& func,
    double x,
    double epsilon
);

/**
 * @brief Approximate a root of f(x) = 0 using the Newton-Raphson method. Algorithm
 * 2.3 in "Numerical Analysis".
 *
 * @param func Continuous function f(x).
 * @param x0 Initial approximation.
 * @param MAX_ITERS Maximum number of iterations.
 * @param TOL Convergence tolerance.
 * @return Approximate x to solution f(x) = 0 with initial approximation.
 */
double newton_method(
    const std::function<double(double)>& func,
    double x0,
    int MAX_ITERS,
    double TOL
);

/**
 * @brief Approximate a root of f(x) = 0 using the secant method. Algorithm
 * 2.4 in "Numerical Analysis".
 *
 * @param func Continuous function f(x).
 * @param x0 First initial approximation.
 * @param x1 Second initial approximation.
 * @param MAX_ITERS Maximum number of iterations.
 * @param TOL Convergence tolerance.
 * @return Approximate x to solution f(x) = 0 with initial approximations.
 */
double secant_method(
    const std::function<double(double)>& func,
    double x0,
    double x1,
    int MAX_ITERS,
    double TOL
);

/**
 * @brief Approximate a root of f(x) = 0 using the false position method. Algorithm
 * 2.5 in "Numerical Analysis".
 *
 * @param func Continuous function f(x).
 * @param x0 First initial approximation.
 * @param x1 Second initial approximation.
 * @param MAX_ITERS Maximum number of iterations.
 * @param TOL Convergence tolerance.
 * @return Approximate x to solution f(x) = 0 with initial approximations.
 */
double false_position(
    const std::function<double(double)>& func,
    double x0,
    double x1,
    int MAX_ITERS,
    double TOL
);