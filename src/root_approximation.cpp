#include <cmath>
#include <iostream>
#include <stdexcept>
#include <tuple>
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

/**
 * @brief Find a solution to f(x) = x using Steffensen's method. Algorithm
 * 2.6 in "Numerical Analysis".
 *
 * @param func Continuous function f(x).
 * @param x0 First initial approximation.
 * @param MAX_ITERS Maximum number of iterations.
 * @param TOL Convergence tolerance.
 * @return Approximate x to solution f(x) = 0.
 */
double steffensen_method(
    const std::function<double(double)>& func,
    double x0,
    int MAX_ITERS,
    double TOL
){
    double x1, x2, x;

    // Step 1
    int iteration = 1;

    // Step 2
    while (iteration <= MAX_ITERS) {
        // Step 3
        x1 = func(x0);
        x2 = func(x1);
        x = x0 - (x1 - x0) * (x1 - x0) / (x2 - 2 * x1 + x0);

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
    std::cerr << "Steffensen's Method not converged after " << MAX_ITERS << " iterations. "
              << "Final tolerance is " << std::abs(x - x0) << std::endl;
    return x;
}

/**
 * @brief Evaluate the polynomial P(x) and its derivative at x0 using Horner's
 * method. Algorithm 2.7 in "Numerical Analysis".
 *
 * @param n The degree of the polynomial.
 * @param coefs List of length n+1 of polynomial coefficients.
 * @param x0 Value that is being evaluated.
 * @return Tuple of the polynomial and derivative at x0.
 */
std::tuple<double, double> horners(int n, const double coefs[], double x0){
    if (n < 0) {
        throw std::invalid_argument("Horner's expects non-negative polynomial degree");
    }

    if (n == 0) {
        return {coefs[0], 0.0};
    }

    // Step 1
    double y = coefs[0];
    double z = coefs[0];

    // Step 2
    for (int jj = 1; jj < n; jj++) {
        y = x0 * y + coefs[jj];
        z = x0 * z + y;
    }

    // Step 3
    y = x0 * y + coefs[n];

    // Step 4
    return {y, z};
}

/**
 * @brief Find a solution to f(x) = 0 given 3 approximations using Muller's
 * method. Algorithm 2.8 in "Numerical Analysis".
 *
 * @param func Continuous function f(x).
 * @param p0 First initial approximation.
 * @param p1 Second initial approximation.
 * @param p2 Third initial approximation.
 * @param MAX_ITERS Maximum number of iterations.
 * @param TOL Convergence tolerance.
 * @return Approximate x to solution f(x) = 0.
 */
double mullers(
    const std::function<double(double)>& func,
    double p0,
    double p1,
    double p2,
    int MAX_ITERS,
    double TOL
){
    double p, b, D, E, h;

    // Step 1
    double h1 = p1 - p0;
    double h2 = p2 - p1;
    if (h1 == 0.0 || h2 == 0.0 || (h2 + h1) == 0.0) {
        throw std::invalid_argument("Muller's method requires distinct initial approximations");
    }

    double d1 = (func(p1) - func(p0)) / h1;
    double d2 = (func(p2) - func(p1)) / h2;
    double d = (d2 - d1) / (h2 + h1);
    int iteration = 3;

    // Step 2
    while (iteration <= MAX_ITERS){
        // Step 3
        b = d2 + h2 * d;
        const double f_p2 = func(p2);
        const double discriminant = std::pow(b, 2) - 4 * f_p2 * d;
        if (discriminant < 0.0) {
            throw std::runtime_error("Muller's method encountered a complex discriminant");
        }
        D = std::sqrt(discriminant);

        // Step 4
        if (std::abs(b - D) < std::abs(b + D)){
            E = b + D;
        } else {
            E = b - D;
        }

        // Step 5
        if (E == 0.0) {
            throw std::runtime_error("Muller's method encountered zero denominator");
        }
        h = -2 * f_p2 / E;
        p = p2 + h;

        // Step 6

        if (std::abs(h) < TOL){
            return p;
        }

        // Step 7
        p0 = p1;
        p1 = p2;
        p2 = p;
        h1 = p1 - p0;
        h2 = p2 - p1;
        if (h1 == 0.0 || h2 == 0.0 || (h2 + h1) == 0.0) {
            throw std::runtime_error("Muller's method encountered degenerate interpolation points");
        }
        d1 = (func(p1) - func(p0))/h1;
        d2 = (func(p2) - func(p1))/h2;
        d = (d2 - d1)/(h2 + h1);
        iteration += 1;
    }

    // Step 8
    std::cerr << "Muller's Method failed after " << MAX_ITERS << " iterations." << std::endl;
    return p;
}
