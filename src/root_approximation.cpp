#include <iostream>
#include "numeric/root_approximation.hpp"

/**
 * @brief Approximate a root of f(x) = 0 using the bisection method. Algorithm
 * 2.1 in "Numerical Analysis".
 *
 * @param func Continuous function f(x).
 * @param a Left endpoint of the interval.
 * @param b Right endpoint of the interval.
 * @param MAX_ITERS Maximum number of iterations.
 * @param TOL Convergence tolerance.
 * @return Approximate root x such that f(x) is near zero.
 */
double bisection(
    const std::function<double(double)>& func,
    double a,
    double b,
    int MAX_ITERS,
    double TOL
){
    double f_a, f_x, x;

    // Step 1
    int iteration = 1;
    f_a = func(a);

    // Step 2
    while (iteration <= MAX_ITERS) {
        // Step 3
        x = a + 0.5 * (b - a);
        f_x = func(x);

        // Step 4
        if (f_x == 0 || 0.5 * (b - a) < TOL) {
            return x;
        }
        // Step 5
        iteration += 1;

        // Step 6
        if (f_a * f_x > 0) {
            a = x;
            f_a = f_x;
        } else {
            b = x;
        }
    }

    // Step 7
    std::cerr << "Bisection Method not converged after " << MAX_ITERS << " iterations. "
              << "Final tolerance is " << 0.5 * (b - a) << std::endl;
    return x;
}


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
){

    double x;

    // Step 1
    int iteration = 1;

    // Step 2
    while (iteration <= MAX_ITERS) {
        // Step 3
        x = func(x0);

        // Step 4
        if (std::abs(x - x0) < TOL) {
            return x;
        }

        // Step 5
        iteration += 1;

        // Step 6
        x0 = x;
    }

    // Step 7
    std::cerr << "Fixed Point Iteration not converged after " << MAX_ITERS << " iterations. "
              << "Final tolerance is " << std::abs(x - x0) << std::endl;

    return x;
}
