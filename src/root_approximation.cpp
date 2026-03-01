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
){
    double numerator = func(x + epsilon) - func(x - epsilon);
    double denominator = 2 * epsilon;
    return numerator / denominator;
}

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
){
    double fdx_x, x;

    // Step 1
    int iteration = 1;

    // Step 2
    while (iteration <= MAX_ITERS) {
        // Step 3
        fdx_x = first_derivative(func, x0, 1e-3);
        x = x0 - func(x0) / fdx_x;

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
    std::cerr << "Newton's Method not converged after " << MAX_ITERS << " iterations. "
              << "Final tolerance is " << std::abs(x - x0) << std::endl;
    return x;
}

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
){
    double f_x0, f_x1, x;

    // Step 1
    int iteration = 2;
    f_x0 = func(x0);
    f_x1 = func(x1);

    // Step 2
    while (iteration <= MAX_ITERS) {
        // Step 3
        x = x1 - f_x1 * (x1 - x0) / (f_x1 - f_x0);

        // Step 4
        if (std::abs(x - x1) < TOL) {
            return x;
        }

        // Step 5
        iteration += 1;

        // Step 6
        x0 = x1;
        x1 = x;
        f_x0 = f_x1;
        f_x1 = func(x);
    }

    // Step 7
    std::cerr << "Secant Method not converged after " << MAX_ITERS << " iterations. "
              << "Final tolerance is " << std::abs(x - x1) << std::endl;
    return x;

}

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
){
    double f_x0, f_x1, x, f_x;

    // Step 1
    int iteration = 2;
    f_x0 = func(x0);
    f_x1 = func(x1);

    // Step 2
    while (iteration <= MAX_ITERS) {
        // Step 3
        x = x0 - f_x0 * (x1 - x0) / (f_x1 - f_x0);

        // Step 4
        if (std::abs(x - x1) < TOL) {
            return x;
        }

        // Step 5
        iteration += 1;
        f_x = func(x0);

        // Step 6
        if (f_x1 * f_x < 0) {
            x0 = x1;
            f_x0 = f_x1;
        }

        // Step 7
        x1 = x;
        f_x1 = func(x);
    }

    // Step 8
    std::cerr << "False Position Method not converged after " << MAX_ITERS << " iterations. "
              << "Final tolerance is " << std::abs(f_x) << std::endl;
    return x;
}