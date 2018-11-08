#include <iostream>
#include <vector>
#include <memory>
#include <cxxabi.h>

template <class T>
std::string type_name()
{
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own(
#ifndef _MSC_VER
    abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
#else
    nullptr,
#endif
    std::free);

    std::string r = own != nullptr ? own.get() : typeid(TR).name();

    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";

    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";

    return r;
}

int main()
{
    int a = 0, b = 0;
    const auto cpi = &a;
    auto pi = &b;

    std::cout << "typeid cpi : " << *cpi << " type: " << typeid(cpi).name() << "\n" <<
                 "typeid  pi : " << *pi << " type: " << typeid(pi).name() << std::endl;

    std::cout << "type_name cpi: " << type_name<decltype(cpi)>() << '\n';
    std::cout << "type_name  pi: " << type_name<decltype(pi)>() << '\n';
                            
    const int ci = 0;
    const auto cpci = &ci;
    std::cout << "type_name cpci: " << type_name<decltype(cpci)>() << '\n';

    return 0;
}

