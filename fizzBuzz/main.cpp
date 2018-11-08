/*
Write a program that prints the numbers from 1 to 100.
But for multiples of three print “Fizz” instead of the number and for the multiples of five print “Buzz”.
For numbers which are multiples of both three and five print “FizzBuzz”.
*/
#include <iostream>
#include <limits>
#include <vector>
#include <memory>

using namespace std;

void pressEnterToContinue()
{
    cout << "press ENTER to continue" << endl;
    getchar();
}


int main()
{
    for (int i = 1; i < 101; ++i)
    {
        bool printed = false;
        cout << i << " : ";
        if (i % 3 == 0) {
            cout << "Fizz";
            printed = true;
        }
        if (i % 5 == 0) {
            cout << "Bizz";
            printed = true;
        }
        if (!printed) {
            cout << i;
        }
        cout << endl;
        if (i % 10 == 0) {
            cout << endl;
        }
    }

    return 0;
}

