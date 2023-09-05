// Ira Narang
// EID: in2933
// TACC username: iranarang

#include <iostream>
using namespace std; //add iostream and std libraries

int main() { //set up main

    int num;
    int longest = 0; //initiate variables
 
    for(int i = 1; i<=1000; i++) { //set up for loop to go through all 1000 numbers
        int length = 1; //initialize temporary length of sequence
        num = i;
        int tempnum = i;
        
        while (num > 1) { //use while loop to keep running conditionals until the sequence reaches 1
            length++;
            if (num % 2 == 0) //using given conditions
                num = num/2;
            else if (num % 2 == 1)
                num = num*3 + 1;
            
        }
        if (length > longest) { //keep track of the longest sequence by storing the value each time the length increases
            longest = length;
            cout << "The starting number of the longest sequence is: " << tempnum << endl; //print out the starting number to each sequence that is longer      
        }
    }

}