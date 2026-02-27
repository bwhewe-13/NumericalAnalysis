#include <cmath>
#include <functional>

#include <catch2/catch_test_macros.hpp>

#include "numeric/root_approximation.hpp"

TEST_CASE("bisection solves linear root", "[bisection]") {
    const std::function<double(double)> function = [](double x) { return 2.0 * x - 1.0; };
    const double approx = bisection(function, -1.0, 1.0, 100, 1e-8);
    const double reference = 0.5;

    REQUIRE(std::abs(approx - reference) < 1e-8);
}

TEST_CASE("bisection solves cubic root", "[bisection]") {
    const std::function<double(double)> function = [](double x) {
        return x * x * x + 4.0 * x * x - 10.0;
    };
    const double approx = bisection(function, 1.0, 2.0, 100, 1e-8);
    const double reference = 1.36523001341410;

    REQUIRE(std::abs(approx - reference) < 1e-8);
}

TEST_CASE("fixed point converges for transformed cubic", "[fixed_point]") {
    const std::function<double(double)> function = [](double x) {
        return 0.5 * std::sqrt(10.0 - x * x * x);
    };
    const double approx = fixed_point(function, 1.5, 100, 1e-8);
    const double reference = function(approx);

    REQUIRE(std::abs(approx - reference) < 1e-8);
}

TEST_CASE("fixed point approximates sqrt2", "[fixed_point]") {
    const std::function<double(double)> function = [](double x) {
        return 0.5 * (x + 2.0 / x);
    };
    const double approx = fixed_point(function, 1.0, 100, 1e-8);
    const double reference = 1.41421356237310;

    REQUIRE(std::abs(approx - reference) < 1e-8);
}
