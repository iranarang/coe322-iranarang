#include <iostream>
using namespace std;

int main() {

    int num;
    int longest = 0;
 
    for(int i = 1; i<=1000; i++) {
        int length = 0;
        num = i;
        int tempnum = i;
        
        while (num > 1) {
            length++;
            if (num % 2 == 0)
                num = num/2;
            else if (num % 2 == 1)
                num = num*3 + 1;
            
        }
        if (length > longest) {
            longest = length;
            cout << "The starting number of the longest sequence is: " << tempnum << endl;       
        }
    }

}