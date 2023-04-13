/*
To compile and run
cl /EHsc /I .\include\ main.cpp .\src\*.cpp

.\main.exe

References
https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-alphabetically?view=msvc-170
https://learn.microsoft.com/en-us/cpp/build/reference/output-file-f-options?view=msvc-170
*/


#include <iostream>
#include "InstructionMemory.hpp"

/*
General TODOs
- Implement Register Memory
- Implement Data Memory
- Define I/R/J type instructions
    - Define funct codes within these types
- Finish ALU implementation

*/


int main(int arc, char *argv[])
{
    std::cout << "Starting MIPS Emulator" << std::endl;

    // Initialize instruction memory to hold 4096 instructions
    InstructionMemory instrMem(4096); 


    /*
    Still need following objects:
        Register memory
        Data Memory
    */


    return 0;
}