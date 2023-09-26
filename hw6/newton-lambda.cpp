// Names: Christine Goh, Ira Narang, Rhea Samuel
// UTEIDs: cxg96, in2933, rss3488
// TACC Usernames: christinegoh, iranarang, rheasamuel12 

#include <iostream> 
#include <cmath>
#include <functional>
#include "cxxopts.hpp"
using std::cin;
using std::cout;
using std::function;

/**
 * Function to calculate x using newton formula
 * 
 * Inputs: Lambda functions f and fprime
 * Output: double x 
 *
 */

double newton_formula(function<double(double)> f, function<double(double)> fprime) {
    double x{1.}; // initialize x
    while (true) {
        auto fx = f(x); //plug in x to input function
        if (std::abs(fx) < 1.e-10) break; //if fx is less than the tolerance, loop ends
        x = x - fx / fprime(x); // newton method formula
        
    }
    return x;
}

/**
 * Function to calculate root for Exercise 4
 *
 * Inputs: Lambda functions f and fprime
 * Output: double x
 *
 */

double newton_root(function<double(double)> f, function<double(double)> fprime) {
    return newton_formula(f, fprime); // return the x calculated using f and fprime
}

/**
 * Function for Exercise 5
 *
 * Input: Lambda function f
 * Output: double x
*/

double newton_root(function<double(double)> f) { // exercise 5 input f only
    double x{1.}; // initialize x
    double h = 1e-6; // initialize tolerance
    
    // Lambda function to approximate the derivative using finite differences
    auto fprime = [f, h](double x) { // use finite difference formula
        return (f(x + h) - f(x)) / h;
    };

    return newton_formula(f, fprime); // return x caluclated using f and fprime
    //return x;
}

int main(int argc,char **argv) {

    cxxopts::Options options
    ("cxxopts",
     "Commandline options demo");
    options.add_options()
    ("n,number", "input number",
    cxxopts::value<double>()	// option for double 
    ->default_value("1.00")	// setting default value
    );

    auto result = options.parse(argc, argv);

    auto number = result["number"].as<double>();
    cout << "Using number: " << number << '\n';
    auto f = [number](double x) { return x * x - number; }; // use lambda function to determine f
    //auto fprime = [number](double x) { return 2 * x; };
    auto root = newton_root(f); // calculate root using f 
    cout << "The root of " << number << " is " << root << '\n'; // print out the root calculated using inputted number    

    return 0;
}
