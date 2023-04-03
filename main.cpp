/*
To compile and run
cl /EHsc /I .\include\ main.cpp .\src\*.cpp

.\main.exe

References
https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-alphabetically?view=msvc-170
https://learn.microsoft.com/en-us/cpp/build/reference/output-file-f-options?view=msvc-170
*/


#include <iostream>
#include "Mux.hpp"


int main(int arc, char *argv[])
{
    std::cout << "starting" << std::endl;

    Mux m;

    return 0;
}