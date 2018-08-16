#include <iostream>
#include <typeinfo>

template<class T>
void foo(){
    std::cout << typeid(T).name() << std::endl;
}

template<class T>
T&& bar(const T& var){
    T ret = var;
    return std::move(ret);
}


int main() {
    foo<int>();
    foo<float>();
    foo<double>();
    foo<char>();
    foo<char*>();
    int a = 10;
    int i = bar<int>(10);
    std::cout << "i:" << i << " a:" << a << std::endl;
    return 0;
}

