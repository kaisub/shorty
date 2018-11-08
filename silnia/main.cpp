#include <iostream>

using namespace std;

constexpr int silnia(int i)
{
    return (i > 1) ? i * silnia(i - 1) : 1;
}

int main()
{
    int val = 3;
    cout << "silnia: " << val << " : " << silnia(val) << endl;
    return 0;
}

