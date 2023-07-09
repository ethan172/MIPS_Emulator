/*
To compile and run
cl /EHsc /I .\include\ main.cpp .\src\*.cpp

.\main.exe

References
https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-alphabetically?view=msvc-170
https://learn.microsoft.com/en-us/cpp/build/reference/output-file-f-options?view=msvc-170
*/


#include <iostream>
#include "MIPSProcessor.hpp"

/*
General TODOs

- Complete ALU operations
- Complete unit testing all components
- Implement reserved memory spaces for register memory
- Check for memory leaks

*/


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage is MIPSEmulator <instruction file>" << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        std::cout << "Reading instructions from " << argv[1] << std::endl;
    }

    MIPSProcessor mp;
    mp.setInstructionBuffer(argv[1]);
    mp.main();
    
    return EXIT_SUCCESS;
}