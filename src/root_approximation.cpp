
#include <iostream>
#include "numeric/root_approximation.hpp"

/**
 * @brief Approximate a root of f(x) = 0 using the bisection method.
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
