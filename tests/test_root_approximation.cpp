#include <cmath>
#include <functional>
#include <stdexcept>

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

TEST_CASE("first derivative approximates quadratic slope", "[first_derivative]") {
    const std::function<double(double)> function = [](double x) {
        return x * x;
    };
    const double approx = first_derivative(function, 2.0, 1e-3);
    const double reference = 4.0;

    REQUIRE(std::abs(approx - reference) < 1e-3);
}

TEST_CASE("newton method approximates sqrt2", "[newton_method]") {
    const std::function<double(double)> function = [](double x) {
        return x * x - 2.0;
    };
    const double approx = newton_method(function, 1.0, 100, 1e-8);
    const double reference = 1.41421356237310;

    REQUIRE(std::abs(approx - reference) < 1e-8);
}

TEST_CASE("secant method approximates root of cos(x) - x", "[secant_method]") {
    const std::function<double(double)> function = [](double x) {
        return std::cos(x) - x;
    };
    const double p0 = 0.5;
    const double p1 = 0.25 * M_PI;
    const double approx = secant_method(function, p0, p1, 100, 1e-8);
    const double reference = 0.73908513321516064166;

    REQUIRE(std::abs(approx - reference) < 1e-8);
}

TEST_CASE("secant method approximates cubic root", "[secant_method]") {
    const std::function<double(double)> function = [](double x) {
        return x * x * x + 4.0 * x * x - 10.0;
    };
    const double p0 = 1.0;
    const double p1 = 2.0;
    const double approx = secant_method(function, p0, p1, 100, 1e-8);
    const double reference = 1.36523001341410;

    REQUIRE(std::abs(approx - reference) < 1e-8);
}

TEST_CASE("false position approximates root of cos(x) - x", "[false_position]") {
    const std::function<double(double)> function = [](double x) {
        return std::cos(x) - x;
    };
    const double p0 = 0.5;
    const double p1 = 0.25 * M_PI;
    const double approx = false_position(function, p0, p1, 100, 1e-8);
    const double reference = 0.73908513321516064166;

    REQUIRE(std::abs(approx - reference) < 1e-8);
}

TEST_CASE("false position approximates cubic root", "[false_position]") {
    const std::function<double(double)> function = [](double x) {
        return x * x * x + 4.0 * x * x - 10.0;
    };
    const double p0 = 1.0;
    const double p1 = 2.0;
    const double approx = false_position(function, p0, p1, 100, 1e-8);
    const double reference = 1.36523001341410;

    REQUIRE(std::abs(approx - reference) < 1e-8);
}

TEST_CASE("steffensen method approximates transformed cubic root", "[steffensen_method]") {
    const std::function<double(double)> function = [](double x) {
        return std::sqrt(10.0 / (x + 4.0));
    };
    const double approx = steffensen_method(function, 1.5, 100, 1e-8);
    const double reference = 1.36523001341409684576;

    REQUIRE(std::abs(approx - reference) < 1e-8);
}

TEST_CASE("steffensen method converges for transformed cubic fixed-point map", "[steffensen_method]") {
    const std::function<double(double)> function = [](double x) {
        return 0.5 * std::sqrt(10.0 - x * x * x);
    };
    const double approx = steffensen_method(function, 1.5, 100, 1e-8);
    const double reference = function(approx);

    REQUIRE(std::abs(approx - reference) < 1e-8);
}

TEST_CASE("horners evaluates polynomial and derivative case 1", "[horners]") {
    const double coefs[] = {2.0, 0.0, -3.0, 3.0, -4.0};
    const auto [poly_value, derivative_value] = horners(4, coefs, -2.0);

    REQUIRE(std::abs(poly_value - 10.0) < 1e-12);
    REQUIRE(std::abs(derivative_value - (-49.0)) < 1e-12);
}

TEST_CASE("horners evaluates polynomial and derivative case 2", "[horners]") {
    const double coefs[] = {2.0, -6.0, 2.0, -1.0};
    const auto [poly_value, derivative_value] = horners(3, coefs, 3.0);

    REQUIRE(std::abs(poly_value - 5.0) < 1e-12);
    REQUIRE(std::abs(derivative_value - 20.0) < 1e-12);
}

TEST_CASE("horners throws for negative degree", "[horners]") {
    const double coefs[] = {1.0};
    REQUIRE_THROWS_AS(horners(-1, coefs, 0.0), std::invalid_argument);
}

TEST_CASE("mullers approximates cubic root", "[mullers]") {
    const std::function<double(double)> function = [](double x) {
        return x * x * x + 4.0 * x * x - 10.0;
    };
    const double approx = mullers(function, 1.0, 1.5, 2.0, 100, 1e-8);
    const double reference = 1.36523001341410;

    REQUIRE(std::abs(approx - reference) < 1e-8);
}

TEST_CASE("mullers throws for duplicate initial points", "[mullers]") {
    const std::function<double(double)> function = [](double x) {
        return x * x - 2.0;
    };

    REQUIRE_THROWS_AS(mullers(function, 1.0, 1.0, 2.0, 100, 1e-8), std::invalid_argument);
}
