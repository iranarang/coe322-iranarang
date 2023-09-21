// Names: Christine Goh, Ira Narang, Rhea Samuel
// UTEIDs: cxg96, in2933, rss3488
// TACC Usernames: christinegoh, iranarang, rheasamuel12 

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

/**
 * Find prime triples
 * 
 * Input: vector of all primes within the range
 * Prints p,q,r triples
 * 
*/
void findPrimes(std::vector<int> allPrimes) {
    for (int r : allPrimes) {       // Loops through allPrimes vector
        for(int p = 3; p < r; p++){     // Nested for loop that assigns a value p and looks for an equidistant prime q
            if(isPrime(p)){
                int q = 2 * r - p;      // Equation for finding q
                if (q > p && isPrime(q)) {  
                    std::cout << "p = " << p << ", q = " << q << ", r = " << r << std::endl;
                    break;      // Break after finding the first p and q for r
                }
            }
            
        }
        
    }
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

int main(){

    int nprimes;
    cout << "Enter the number of primes: ";
    cin >> nprimes;     // input number of primes to be displayed
    primegenerator sequence;
    std::vector<int> allPrimes;

    while (sequence.number_of_primes_found()<nprimes) {
        int number = sequence.nextprime();
        if(number > 4)
            allPrimes.push_back(number);
        else
            cout<< "No equidistant primes from " << number << std::endl;    // 2 and 3 do not have equidistant primes
    }
    
    findPrimes(allPrimes); 


}