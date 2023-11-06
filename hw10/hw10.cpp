// Names: Christine Goh, Ira Narang, Rhea Samuel
// UTEIDs: cxg96, in2933, rss3488
// TACC Usernames: christinegoh, iranarang, rheasamuel12

#include <iostream>
#include <vector>

#include "hw10.hpp"
using std::cin, std::cout, std::vector;

double f(int n) { return n * n + 1; }

#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"

TEST_CASE("test that f always returns positive")
{
    int n = 5; // change as needed
    REQUIRE(f(n) > 0);
}

// bisect/zeroclasstest.cpp
TEST_CASE("proper test", "[2]")
{
    vector<double> coefficients{3., 2.5, 2.1};
    REQUIRE_NOTHROW(polynomial(coefficients));
    coefficients.at(0) = 0.;
    REQUIRE_THROWS(polynomial(coefficients));
}