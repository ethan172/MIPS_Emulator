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
#include "RegisterMemory.hpp"
#include "ALU.hpp"
#include "MipsUtils.hpp"
#include "ControlUnit.hpp"

/*
General TODOs
- Implement Register Memory
- Implement Data Memory
- Define I/R/J type instructions
    - Define funct codes within these types
- Implement ControlUnit
    - This may have to wait until after instructions are defined

*/


int main(int arc, char *argv[])
{
    std::cout << "Starting MIPS Emulator" << std::endl;

    // read in the instruction file here

    InstructionMemory instructionMem(4096);
    RegisterMemory regMem(512);
    ALU alu;        // full ALU between the register and data memory spaces
    ALU pcAdder;    // adds 4 to the program counter
    

    uint16_t programCounter = 0;
    uint32_t instructionWord;
    bool error = true;
    uint16_t rs, rt, rd, immediate;
    uint32_t reg1Data, reg2Data;
    uint32_t aluResult;

    bool aluZeroFlag, aluOverflowFlag, aluCarryFlag;

    while (programCounter < instructionMem.getInstructionCount())
    {
        // fetch the next instruction
        error &= instructionMem.fetchInstruction(programCounter, instructionWord);

        // Parse out different pieces of the instruction word
        rs = (instructionWord & 0x03E00000) >> 21; // bits 25:21
        rt = (instructionWord & 0x001F0000) >> 16; // bits 20:16
        rd = (instructionWord & 0x0000F800) >> 11; // bits 15:11
        immediate = (instructionWord & 0x00007FFF); // bits 15:0

       error &= regMem.readRegister(rs, reg1Data);
       error &= regMem.readRegister(rt, reg2Data);

       uint16_t aluSrc = 0; // TODO get this from the control unit

       aluResult = alu.evaluate(reg1Data, MIPSUtils::mux(reg2Data, MIPSUtils::signExtend(immediate), aluSrc),
                                aluZeroFlag, aluOverflowFlag, aluCarryFlag);


        if (!error)
        {
            // found an error, don't continue
            break;
        }

        programCounter++; // Go to the next instruction
    }



    /*
    General control flow
    Read in the file containing the instructions (binary for now)
    store off number of instructions in the file
    Initialize the program counter to 0

    while PC < Instruction Count
    {
        fetch instruction[PC]
        mask out different bits going to:
            Control Unit
                - Will give this the whole 32bit instruction
                - Will not have ALU Control module, just pass the last 5 bits via ALUOp
            Register Memory
    }
    */


    return 0;
}