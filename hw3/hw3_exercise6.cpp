// Ira Narang
// EID: in2933
// TACC username: iranarang

#include <iostream> //add iostream, vector, and std libraries
#include <vector>
using namespace std;

void exercise6(vector<int> numbers) { //create function to accept input of numbers

    vector<int> odds; //separate the numbers into odds and events
    vector<int> evens;
    int length = numbers.size();

    for (int i=0; i < length; i++) { //go through each number in the input

        if (numbers[i] % 2 == 0) { //if number is even add to even vector
            evens.push_back(numbers[i]);
        }
        else if (numbers[i] % 2 == 1) { //if number is odd add to odd vector
            odds.push_back(numbers[i]);
        }
    }

    cout << "Even vector: "; //print out even vector
    for (int i=0; i<evens.size(); i++) {

        cout << evens[i] << " ";
    }
    cout << endl;
    cout << "Odd vector: "; //print out odd vector
    for (int i=0; i<odds.size(); i++) {

        cout << odds[i] << " ";
    }

}


int main() {

    vector<int> numbers = {1, 2, 3, 4, 5}; //add input

    exercise6(numbers); //call the function

}