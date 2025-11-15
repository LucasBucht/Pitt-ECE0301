#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <stdexcept>
#include <cmath>

#include "Frequency.hpp"

const double THRESHOLD = 1e-9;

/* Provided test cases */

// TEST_CASE("Export example", "[frequency]"){
//     Frequency fdef;
//     fdef.gaussian(12.0, 9*M_PI);
//     fdef.export_csv("output");
// }

TEST_CASE("Test default construction", "[frequency]") {
    Frequency fdef;

    REQUIRE(fdef.get_component() == 301);
    REQUIRE(std::abs(fdef.get_increment() - 0.1) <= THRESHOLD);
}

TEST_CASE("Test construction with arguments", "[frequency]") {
    int comp = 201;
    double incr = 0.02;
    Frequency farg(comp, incr);

    REQUIRE(farg.get_component() == comp);
    REQUIRE(std::abs(farg.get_increment() - incr) <= THRESHOLD);

    // must call the frequency constructor directly to check throws in constructor
    // invalid number of components
    REQUIRE_THROWS_AS(Frequency(-1, incr), std::invalid_argument);
    REQUIRE_THROWS_AS(Frequency(Frequency::MAX_COMPONENTS_NUM + 1, incr), std::invalid_argument);
    // invalid incr
    REQUIRE_THROWS_AS(Frequency(comp, -1), std::invalid_argument);
    REQUIRE_THROWS_AS(Frequency(comp, 0), std::invalid_argument);
}

TEST_CASE("Test default construction zeros", "[frequency]") {
    Frequency zero;

    const int comp = zero.get_component();
    double incr = zero.get_increment();

    // arrays to hold exported data
    double freqs[comp];
    double amps[comp];

    zero.export_frequency(freqs, amps);

    for (int i = 0; i < comp; i++)
    {
        // check freq component according to equation
        double freq_diff = std::abs(freqs[i] - static_cast<double>(i) * incr);
        REQUIRE(freq_diff <= THRESHOLD);
        // all amps should be zero
        double amp_diff = std::abs(amps[i] - 0);
        REQUIRE(amp_diff <= THRESHOLD);
    }
}

/* Add your test cases below */

TEST_CASE("Test constant function", "[frequency]") {
    Frequency f;
    double val = 5.0;
    f.constant(val);

    const int comp = f.get_component();
    double incr = f.get_increment();

    double freqs[comp], amps[comp];
    f.export_frequency(freqs, amps);

    for (int i = 0; i < comp; i++) {
        REQUIRE(std::abs(freqs[i] - static_cast<double>(i) * incr) <= THRESHOLD);
        REQUIRE(std::abs(amps[i] - val) <= THRESHOLD);
    }

    // invalid case
    REQUIRE_THROWS_AS(f.constant(-3.2), std::invalid_argument);
}

TEST_CASE("Test gaussian function", "[frequency]") {
    Frequency f;
    double A = 2.0;
    double alpha = 0.5;
    f.gaussian(A, alpha);

    const int comp = f.get_component();
    double freqs[comp], amps[comp];
    f.export_frequency(freqs, amps);

    for (int i = 0; i < comp; i++) {
        double w = freqs[i];
        double expected = A * std::sqrt(M_PI / alpha) * std::exp(-(w * w) / (4.0 * alpha));
        REQUIRE(std::abs(amps[i] - expected) <= 1e-6);
    }

    // invalid arguments
    REQUIRE_THROWS_AS(f.gaussian(-1.0, 0.5), std::invalid_argument);
    REQUIRE_THROWS_AS(f.gaussian(2.0, 0.0), std::invalid_argument);
}

TEST_CASE("Operator == comparison", "[frequency]") {
    Frequency f1, f2;

    f1.constant(1.0);
    f2.constant(1.0);
    REQUIRE(f1 == f2);

    f2.constant(2.0);
    REQUIRE_FALSE(f1 == f2);

    Frequency f3(200, 0.1);
    REQUIRE_FALSE(f1 == f3);
}

TEST_CASE("Operator <= comparison", "[frequency]") {
    Frequency f1, f2;
    f1.constant(2.0);
    f2.constant(3.0);
    REQUIRE(f1 <= f2);

    f2.constant(1.0);
    REQUIRE_FALSE(f1 <= f2);

    // Mismatched component count
    Frequency f3(200, 0.1);
    REQUIRE_THROWS_AS(f1 <= f3, std::logic_error);
}

TEST_CASE("Operator >> comparison", "[frequency]") {
    Frequency f1, f2;
    f1.constant(100.0);
    f2.constant(1.0);

    // >100x
    REQUIRE(f1 >> f2);

    // <100x
    REQUIRE_FALSE(f2 >> f1);
}

TEST_CASE("Operator ^ comparison", "[frequency]") {
    Frequency f1(5, 0.1);
    Frequency f2(3, 0.1);

    f1.constant(2.0);
    f2.constant(4.0);

     // Multiply
    Frequency f3 = f1 ^ f2;

    REQUIRE(f3.get_component() == 5);
    double freqs[5], amps[5];
    f3.export_frequency(freqs, amps);

    // First 3 components multiplied
    for (int i = 0; i < 3; i++)
        REQUIRE(std::abs(amps[i] - (2.0 * 4.0)) <= THRESHOLD);

    // Remaining 2 components zero
    for (int i = 3; i < 5; i++)
        REQUIRE(std::abs(amps[i]) <= THRESHOLD);

    // Mismatch increment
    Frequency f4(5, 0.2);
    REQUIRE_THROWS_AS(f1 ^ f4, std::logic_error);
}

TEST_CASE("Checkoff Test Case C", "[frequency]"){
    Frequency a(100, 0.3);
    Frequency b(100, 0.5);
    REQUIRE_THROWS_AS(a <= b, std::logic_error);
    REQUIRE_NOTHROW(a >> b);
}