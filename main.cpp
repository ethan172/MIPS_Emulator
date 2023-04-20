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
#include "InstructionTypes.hpp"
#include "DataMemory.hpp"

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
    DataMemory dataMem(8192);


    // ALU in top left of diagram
    ALU pcAdder;    // adds 4 to the program counter
    bool pcAdderZero, pcAdderCarry, pcAdderOverflow;
    uint32_t pcAdderResult;
    pcAdder.setOpCode(ALU::ALUOpCodes::Add); // This ALU will only ever add


    ALU branchAlu;  // ALU to handle adding the branches
    bool branchAluZero, branchAluCarry, branchAluOverflow;
    uint32_t branchAluResult;
    branchAlu.setOpCode(ALU::ALUOpCodes::Add); // This ALU will only ever add
    

    uint16_t programCounter = 0;
    uint32_t instructionWord;
    bool error = true;
    uint16_t rs, rt, rd, immediate, funct;
    uint32_t reg1Data, reg2Data;
    uint32_t aluResult, signExtendImm;

    // Control signal variables
    bool regDest, branch, memRead, memToReg, memWrite, aluSrc, regWrite;
    uint8_t aluOp;

    bool aluZeroFlag, aluOverflowFlag, aluCarryFlag;

    while (programCounter < instructionMem.getInstructionCount())
    {
        /*
        Diagram has PC + 4 but here it is PC + 1. This is because normally +4 will get you +4 bytes (32 bits)
        but since this MIPS Emulator implementation uses arrays we just need to add 1 to the index
        */
        pcAdderResult = pcAdder.evaluate(programCounter, 1, pcAdderZero, pcAdderOverflow, pcAdderCarry);
        error &= instructionMem.fetchInstruction(programCounter, instructionWord);


        // Parse out different pieces of the instruction word
        rs = (instructionWord & RTypeInstruction::RsMask) >> 21; // bits 25:21
        rt = (instructionWord & RTypeInstruction::RtMask) >> 16; // bits 20:16
        rd = (instructionWord & RTypeInstruction::RdMask) >> 11; // bits 15:11
        immediate = (instructionWord & ITypeInstruction::ImmediateMask); // bits 15:0
        funct = (instructionWord & RTypeInstruction::FunctMask); // bits 5:0

        error &= regMem.getRegister(rs, reg1Data);
        error &= regMem.getRegister(rt, reg2Data);

        ControlUnit::evaluate(instructionWord, regDest, branch, memRead, memToReg, aluOp,
                                                memWrite, aluSrc, regWrite);

        signExtendImm = MIPSUtils::signExtend(immediate);


        alu.setOpCode(aluOp); // Set ALU opcode from control unit signals
        aluResult = alu.evaluate(reg1Data, MIPSUtils::mux(reg2Data, signExtendImm, aluSrc),
                                aluZeroFlag, aluOverflowFlag, aluCarryFlag);

        branchAluResult = branchAlu.evaluate(pcAdderResult, (signExtendImm << 2), 
                                            branchAluZero, branchAluOverflow, branchAluCarry);


        
        // TODO put the data memory access here


        programCounter = MIPSUtils::mux(pcAdderResult, branchAluResult, (aluZeroFlag && branch));

        if (aluOverflowFlag || aluCarryFlag)
        {
            // handle the overflow somehow?
        }



        if (!error)
        {
            // found an error, don't continue
            break;
        }
    }

    
    return 0;
}