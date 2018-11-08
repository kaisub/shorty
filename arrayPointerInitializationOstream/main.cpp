#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <typeinfo>
#include <map>
#include <memory>
#include <cxxabi.h>

using namespace std;

class A
{
public:
    int _m = 1;
    A() {}
    A(int p_m) : _m(p_m) {}

    int operator()() { return _m; }
    friend std::ostream& operator<< (std::ostream&, const A&);
};

std::ostream& operator<< (std::ostream& p_stream, const A& p_a)
{
    p_stream << p_a._m;
    return p_stream;
}

constexpr size_t ARR_SIZE = 5;

void printArray(const array<A*, ARR_SIZE> & p_arr)
{
    for (auto & item : p_arr)
    {
        cout << *item << endl;
    }
    cout << endl;
}

int main()
{
    array<A*, ARR_SIZE> arr;
    arr.fill(new A());
    printArray(arr);

    arr[2] = new A(33);
    arr[4] = new A(55);
    printArray(arr);

    int iter = 2;
    for (A*& item : arr)
    {
        item = new A(iter++);
    }
    printArray(arr);

    for_each(arr.begin(), arr.end(), [&iter](A*& a){ a = new A(iter++); });
    printArray(arr);

    transform(arr.begin(), arr.end(), arr.begin(), [&iter](A*&){ return new A(iter++); });
    printArray(arr);

    return 0;
}

