#include <iostream>
#include <typeinfo>
#include <functional>


//template basico
template<class T>
void foo(){
    std::cout << typeid(T).name() << std::endl;
}

//uso del parametro del template
template<class T>
T&& bar(const T& var){
    T ret = var;
    return std::move(ret);
}

//especializacion
float&& bar(const float& var){
    std::cout << "Called bar template specialization for float" << std::endl;
    float ret = var;
    return std::move(ret);
}

//templating default arguments
template <class T=int>
T&& add(const T& a, const T& b)
{
   return std::move(a + b);
}

//templating nontype objects
template <unsigned int N=10>
std::function<int&&(const int& n)> build_add_function() {
    return [](const int& n)->int&&{std::move(n+N);};
}


int main() {
    std::cout << "Types from template foo" << std::endl;
    foo<int>();
    foo<float>();
    foo<double>();
    foo<char>();
    foo<char*>();
    std::cout << std::endl;

    std::cout << "Simple template bar" << std::endl;
    int a = 10;
    int i = bar<int>(a);
    std::cout << "i:" << i << " a:" << a << std::endl;
    std::cout << std::endl;

    std::cout << "Simple specialized(float) template bar" << std::endl;
    float aa = 10.f;
    float ii = bar(aa);
    std::cout << "ii:" << ii << " aa:" << aa << std::endl;
    std::cout << std::endl;

    std::cout << "Simple default argument template add" << std::endl;
    int added_n{add(10, 10)};
    std::cout << added_n << std::endl;
    std::cout << std::endl;

    std::cout << "Simple default argument template add using other type" << std::endl;
    float added_n2{add<float>(5.5f, 5.5f)};
    std::cout << added_n2 << std::endl;
    std::cout << std::endl;

    std::cout << "Function factory template using non-typed argument" << std::endl;
    auto f  = build_add_function();
    auto ff = build_add_function<20>();
    std::cout << f(1) << " <-> " << ff(1) << std::endl;
    return 0;
}