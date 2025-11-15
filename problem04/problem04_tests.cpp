#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <cmath>

#include "circuits.hpp"

// DEFAULT TEST CASES
TEST_CASE("Test Current", "[Circuits]")
{
    double resistance = 1000;
    double power = 2.5000;
    REQUIRE(get_current(resistance, power) == sqrt(power / resistance));
}

TEST_CASE("Test Resistance", "[Circuits]")
{
    double current = 0.05;
    double power = 2.5000;
    REQUIRE(get_resistance(current, power) == power / pow(current, 2));
}

TEST_CASE("Test Power", "[Circuits]")
{
    double current = 0.05;
    double resistance = 1000;
    REQUIRE(get_power(current, resistance) == pow(current, 2) * resistance);
}

TEST_CASE("Test getValue Parsing", "[Circuits]")
{
    std::string test_string = "R = 1000.0";
    REQUIRE(get_value(test_string) == 1000.0);
}



// ADDED TEST CASES 8A
TEST_CASE("Test Current 2", "[Circuits]")
{
    double resistance = 50;
    double power = 0.5;
    REQUIRE(get_current(resistance, power) == sqrt(power / resistance));
}

TEST_CASE("Test Resistance 2", "[Circuits]")
{
    double current = 1;
    double power = 3.65;
    REQUIRE(get_resistance(current, power) == power / pow(current, 2));
}

TEST_CASE("Test Power 2", "[Circuits]")
{
    double current = 2;
    double resistance = 8500;
    REQUIRE(get_power(current, resistance) == pow(current, 2) * resistance);
}



// ADDED TEST CASES 8B

TEST_CASE("Test getValue Parsing (Valid)", "[Circuits]")
{
    std::string test_string = "I = 2.0";
    REQUIRE(get_value(test_string) == 2.0);
}

TEST_CASE("Test getValue Parsing (Invalid)", "[Circuits]")
{
    std::string test_string = "R 100.0";
    REQUIRE(get_value(test_string) == -1);

    test_string = "R = x100.0";
    REQUIRE(get_value(test_string) == -1);
}



// ADDED TEST CASES 8C

TEST_CASE("Test Current (Negative)", "[Circuits]")
{
    double resistance = -50;
    double power = 0.5;
    REQUIRE(get_current(resistance, power) == -1);

    resistance = 50;
    power = -0.5;
    REQUIRE(get_current(resistance, power) == -1);
}

TEST_CASE("Test Resistance (Negative)", "[Circuits]")
{
    double current = -1;
    double power = 3.65;
    REQUIRE(get_resistance(current, power) == -1);

    current = 1;
    power = -3.65;
    REQUIRE(get_resistance(current, power) == -1);
}

TEST_CASE("Test Power (Negative)", "[Circuits]")
{
    double current = -2;
    double resistance = 8500;
    REQUIRE(get_power(current, resistance) == -1);

    current = 2;
    resistance = -8500;
    REQUIRE(get_power(current, resistance) == -1);
}



// VOLTAGE DIVIDER TEST CASES 9

TEST_CASE("Test Voltage Divider (Valid)", "[Circuits]")
{
    double source_power = 10;
    double resistance1 = 1000;
    double resistance2 = 500;
    REQUIRE(get_divider_power(source_power, resistance1, resistance2) == source_power * (resistance2 / (resistance1 + resistance2)));
}

TEST_CASE("Test Voltage Divider (Invalid)", "[Circuits]")
{
    double source_power = -5;
    double resistance1 = 2500;
    double resistance2 = 300;
    REQUIRE(get_divider_power(source_power, resistance1, resistance2) == -1);

    source_power = 5;
    resistance1 = -2500;
    resistance2 = 300;
    REQUIRE(get_divider_power(source_power, resistance1, resistance2) == -1);

    source_power = 5;
    resistance1 = 2500;
    resistance2 = -300;
    REQUIRE(get_divider_power(source_power, resistance1, resistance2) == -1);

}