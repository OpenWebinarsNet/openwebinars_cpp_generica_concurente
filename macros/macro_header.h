#ifndef __MACRO_HEADER_H__ //warding macro
#define __MACRO_HEADER_H__

    //conditional compilation
    #ifdef DEBUG
        #define MY_VAR_MACRO "Hello world from debug"
    #else
        #define MY_VAR_MACRO "Hello world from release"
    #endif

#endif //__MACRO_HEADER_H__
