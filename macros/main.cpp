#define DEBUG true //WARNING: DEBUG manual defined, better using cmake


#include <iostream>
#include <string>
#include "macro_header.h"

//macro define
#define MY_FST_MACRO "Hello world"


//macro redifine
#define MY_REDEFINED_MACRO(the_variable) #the_variable
#define MY_REDEFINED_MACRO(the_variable) #the_variable#the_variable


//macros are non-recursive
#define FAC(n) (n>1)?n*FAC(n-1):1

#define SQUARE(x) x*x
//#define SQUARE(x) ((x)*(x))

int main() {

    //macro substitution
    std::cout << MY_FST_MACRO << std::endl;

    //macro redefinition
    std::cout << MY_REDEFINED_MACRO(10) << std::endl;

    //macro recursive error, doesn't work
    //std::cout << FAC(10) << std::endl;

    //fun with macros...what is the output

    std::cout << SQUARE(10)  << std::endl; //10*10 = 100
    std::cout << SQUARE(5+2) << std::endl; //7*7 = 49? or 5+2*5+2?

    std::cout << SQUARE(5+2) << std::endl; //7*7 = 49? or 5+2*5+2?



    //macro conditional compilation
    std::cout << MY_VAR_MACRO << std::endl;


    //macro utils
    for(auto& s : {__DATE__, __TIME__, __FILE__, std::to_string(__LINE__).c_str()}){
        std::cout << s << std::endl;
    }
    return 0;
}