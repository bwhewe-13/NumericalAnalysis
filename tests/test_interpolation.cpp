#include <cmath>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "numeric/interpolation.hpp"

TEST_CASE("neville interpolates a quadratic exactly", "[neville]") {
    const std::vector<double> xn = {1.0, 2.0, 4.0};
    const std::vector<double> fn = {1.0, 4.0, 16.0};  // f(x) = x^2
    const double approx = neville(3.0, xn, fn);
    const double reference = 9.0;

    REQUIRE(std::abs(approx - reference) < 1e-8);
}

TEST_CASE("neville interpolates a cubic exactly", "[neville]") {
    const std::vector<double> xn = {0.0, 1.0, 2.0, 3.0};
    const std::vector<double> fn = {-10.0, -5.0, 14.0, 53.0};  // f(x) = x^3 + 4x^2 - 10
    const double approx = neville(1.5, xn, fn);
    const double reference = 2.375;

    REQUIRE(std::abs(approx - reference) < 1e-8);
}

TEST_CASE("newton returns divided-difference diagonal for a quadratic", "[newton]") {
    const std::vector<double> xn = {1.0, 2.0, 4.0};
    const std::vector<double> fn = {1.0, 4.0, 16.0};  // f(x) = x^2
    const std::vector<double> coefs = newton(xn, fn);
    const std::vector<double> reference = {1.0, 3.0, 1.0};

    REQUIRE(coefs.size() == reference.size());
    for (size_t i = 0; i < reference.size(); ++i) {
        REQUIRE(std::abs(coefs[i] - reference[i]) < 1e-8);
    }
}

TEST_CASE("newton returns divided-difference diagonal for a cubic", "[newton]") {
    const std::vector<double> xn = {1.0, 2.0, 3.0};
    const std::vector<double> fn = {-5.0, 14.0, 53.0};  // f(x) = x^3 + 4x^2 - 10
    const std::vector<double> coefs = newton(xn, fn);
    const std::vector<double> reference = {-5.0, 19.0, 10.0};

    REQUIRE(coefs.size() == reference.size());
    for (size_t i = 0; i < reference.size(); ++i) {
        REQUIRE(std::abs(coefs[i] - reference[i]) < 1e-8);
    }
}
