// Ira Narang
// EID: in2933
// TACC username: iranarang

#include <iostream>
#include <vector>
using namespace std;

int main() {

    //vector<int> numbers = {1, 2, 3, 4, 5};
    vector<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_back(4);
    numbers.push_back(5);
    vector<int> odds;
    vector<int> evens;
    int length = numbers.size();

    for (int i=0; i < length; i++) {

        if (numbers[i] % 2 == 0) {
            evens.push_back(numbers[i]);
        }
        else if (numbers[i] % 2 == 1) {
            odds.push_back(numbers[i]);
        }
    }

    cout << "Even vector: ";
    for (int i=0; i<evens.size(); i++) {

        cout << evens[i] << " ";
    }
    cout << endl;
    cout << "Odd vector: ";
    for (int i=0; i<odds.size(); i++) {

        cout << odds[i] << " ";
    }

}