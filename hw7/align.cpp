// Names: Christine Goh, Ira Narang, Rhea Samuel
// UTEIDs: cxg96, in2933, rss3488
// TACC Usernames: christinegoh, iranarang, rheasamuel12 

#include <iostream> 
#include <string>
#include <fmt/format.h>

using fmt::format,fmt::print;

int main() {

    for (int i=0; i<256; i++){      // Loop through all numbers 0 to 255
        print("{:02X} ", i);        // Using Hex number base
        if ((i + 1) % 16 == 0) {    // Checking for F values so new line is printed
            print("\n");
        }
    }

  return 0;
}