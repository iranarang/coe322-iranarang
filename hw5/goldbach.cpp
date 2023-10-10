// Names: Christine Goh, Ira Narang, Rhea Samuel
// UTEIDs: cxg96, in2933, rss3488
// TACC Usernames: christinegoh, iranarang, rheasamuel12 
// we need two generators, one to generate r values, and the other to generate p values

#include <iostream>
#include <vector>
using std::cin;
using std::cout;

/**
 * Check if input number is prime.
 * 
 * Input: integer to be checked
 * Output: boolean result of prime check
 * 
*/
bool isPrime(int num){
    
    if (num <= 1)       // negative numbers, 0, and 1 are never prime numbers
        return false;
    
    for(int i = 2; i <= num/2; i++){    // loop through all numbers num/2 since 2 is the smallest prime number
        if (num % i == 0){      // if num can be divided by i without a remainder it is not prime
            return false;
        }
    }
    return true;
}

class primegenerator{
    private:
        int m_primes_found = 0;     // stores number of primes found
        int m_current_number = 0;   // stores current number
    public:

        /**
         * Keeps track of number of primes found in sequence
         * 
         * Output: number of primes found
         * 
        */
        int number_of_primes_found(){
            return m_primes_found;
        }

        /**
         * Loops through numbers starting from current number until another prime is found
         * 
         * Output: next prime integer
         * 
        */
        int nextprime(){
            m_current_number++;     // start checking number after current number     
            while(!isPrime(m_current_number))   // while current number is not prime, increment current number by 1
                m_current_number++;
            
            m_primes_found++;   // increment primes found by 1
            return m_current_number;    // return current prime number to be printed out 
        }
};

/**
 * Find prime triples
 * 
 * Input: vector of all primes within the range
 * Prints p,q,r triples
 * 
*/
void find_equidistant_primes(std::vector<int> allPrimes) {
    for (int r : allPrimes) {
        primegenerator primes;        
        int p = 2; // Initialize p to 2 since it is the first prime
        while (p <= r) {
            int q = 2 * r - p;
            if (isPrime(q)) {
                std::cout << "p = " << p << ", q = " << q << ", r = " << r << std::endl;
                break; // only prints out one p,q,r pair for each r value
            }
            p = primes.nextprime();
        }
    }
}

int main(){

    int nprimes;
    cout << "Enter the number of primes: ";
    cin >> nprimes;     // input number of primes to be displayed
    primegenerator generator;
    std::vector<int> allPrimes;

    while (generator.number_of_primes_found() < nprimes+2) { // add two to inputted number to account for 2 and 3 having no equidistant primes
        int number = generator.nextprime();
        if(number > 4)
            allPrimes.push_back(number);
    }
    
    find_equidistant_primes(allPrimes); 


}