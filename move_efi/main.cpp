/*
 * c++11
 * create container (vector, deque, array) and measure time and print it;
 * sort the container and measure time and print it
 * can't sort list with std::sort (list is not random access)
*/

#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <chrono>
#include <cstring>
#include <algorithm>
#include <typeinfo>

using namespace std;

class ExpensiveObject
{
private:
    char* data_ = {nullptr};
    size_t size_ = {0};
public:
    ExpensiveObject() {};

    ExpensiveObject(const char* data) : size_(std::strlen(data))
    {
        data_ = new char[size_+1];
        std::strcpy(data_, data);
    }

    ExpensiveObject(const ExpensiveObject& source) : data_(nullptr), size_(source.size_)
    {
        data_ = new char[size_+1];
        std::strcpy(data_, source.data_);
    }

    ExpensiveObject(ExpensiveObject&& rsource) noexcept :
        data_(rsource.data_), size_(rsource.size_)
    {
        rsource.data_ = nullptr;
        rsource.size_ = 0;
    }

    ~ExpensiveObject()
    {
        delete [] data_;
    }

    ExpensiveObject& operator=(const ExpensiveObject& source)
    {
        ExpensiveObject temp(source);
        swap(temp);
        return *this;
    }

    void swap(ExpensiveObject& other)
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
    }

    const char* data() const
    {
        return data_;
    }

    size_t size() const
    {
        return size_;
    }

    bool operator<(const ExpensiveObject& other) const
    {
        if (std::strcmp(data_, other.data_) < 0)
            return true;
        return false;
    }
};

ExpensiveObject expensive_object_generator()
{
    static char txt[] = "abcdefghijklmn";
    static const size_t size = std::strlen(txt);

    std::random_shuffle(txt, txt + size);

    return ExpensiveObject(txt);
}

constexpr size_t CONTAINER_SIZE = 10000;

template <class Container>
Container createFillContainer()
{
    Container container {};
    for (auto i = 0u ; i < CONTAINER_SIZE; ++i)
    {
        container.push_back(expensive_object_generator());
    }
    return container;
}

template <>
array<ExpensiveObject, CONTAINER_SIZE> createFillContainer<array<ExpensiveObject, CONTAINER_SIZE>>()
{
    array<ExpensiveObject, CONTAINER_SIZE> container;
    for (auto i = 0u ; i < CONTAINER_SIZE; ++i)
    {
        container[i] = expensive_object_generator();
    }
    return container;
}

template <class Container, class Time>
void testSort(Container container, Time start)
{
    sort(container.begin(), container.end());

    auto end = chrono::high_resolution_clock::now();
    cout << "Sorting = ";
    cout << chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << " us" << endl;
}

template <class Container>
void performTest()
{
    cout << "Testing " << typeid(Container).name() << endl;

    auto start = chrono::high_resolution_clock::now();
    Container container = createFillContainer<Container>();
    auto end1 = chrono::high_resolution_clock::now();
    cout << "Creating = ";
    cout << chrono::duration_cast<chrono::microseconds>(end1-start).count();
    cout << " us" << endl;

    testSort(container, end1);
}

int main()
{
    performTest<vector<ExpensiveObject>>();

    performTest<deque<ExpensiveObject>>();

    performTest<array<ExpensiveObject, CONTAINER_SIZE>>();

    return 0;
}
