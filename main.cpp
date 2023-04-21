/*
To compile and run
cl /EHsc /I .\include\ main.cpp .\src\*.cpp

.\main.exe

References
https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-alphabetically?view=msvc-170
https://learn.microsoft.com/en-us/cpp/build/reference/output-file-f-options?view=msvc-170
*/


#include <iostream>
#include <fstream>
#include "InstructionMemory.hpp"
#include "RegisterMemory.hpp"
#include "ALU.hpp"
#include "MipsUtils.hpp"
#include "ControlUnit.hpp"
#include "InstructionTypes.hpp"
#include "DataMemory.hpp"

/*
General TODOs
- Implement logic to read in file

*/


int main(int argc, char *argv[])
{
    std::cout << "Starting MIPS Emulator" << std::endl;

    if (argc != 2)
    {
        std::cout << "Usage is MIPSEmulator <instruction file>" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream inFile(argv[1]);
    uint32_t lineNumber = 1;
    uint32_t instructionWord;
    uint16_t programCounter = 0;
    bool success = true; // overall flag to detect an error

    // Instruction memory object and supporting variables
    InstructionMemory instructionMem(4096);
    uint16_t rs, rt, rd, immediate, funct;
    uint32_t signExtendImm;

    inFile >> instructionWord;
    while (!inFile.fail())
    {
        success &= instructionMem.addInstruction(instructionWord);

        if (!success)
        {
            std::cout << "Could not add instruction " << lineNumber << std::endl;
        }
        
        lineNumber++;
        inFile >> instructionWord;
    }    


    RegisterMemory regMem(512);
    uint32_t reg1Data, reg2Data;


    // full ALU between the register and data memory spaces + supporting variables
    ALU alu;
    bool aluZeroFlag, aluOverflowFlag, aluCarryFlag;
    uint32_t aluResult;
    

    DataMemory dataMem(8192);
    uint32_t dataReadValue;


    // ALU in top left of diagram
    ALU pcAdder;    // adds 4 to the program counter
    bool pcAdderZero, pcAdderCarry, pcAdderOverflow;
    uint32_t pcAdderResult;
    pcAdder.setOpCode(ALU::ALUOpCodes::Add); // This ALU will only ever add


    ALU branchAlu;  // ALU to handle adding the branches
    bool branchAluZero, branchAluCarry, branchAluOverflow;
    uint32_t branchAluResult;
    branchAlu.setOpCode(ALU::ALUOpCodes::Add); // This ALU will only ever add
    

    // Control signal variables
    bool regDest, branch, memRead, memToReg, memWrite, aluSrc, regWrite;
    uint8_t aluOp;


    while (programCounter < instructionMem.getInstructionCount())
    {
        /*
        Diagram has PC + 4 but here it is PC + 1. This is because normally +4 will get you +4 bytes (32 bits)
        but since this MIPS Emulator implementation uses arrays we just need to add 1 to the index
        */
        pcAdderResult = pcAdder.evaluate(programCounter, 1, pcAdderZero, pcAdderOverflow, pcAdderCarry);
        success &= instructionMem.fetchInstruction(programCounter, instructionWord);


        // Parse out different pieces of the instruction word
        rs = (instructionWord & RTypeInstruction::RsMask) >> 21; // bits 25:21
        rt = (instructionWord & RTypeInstruction::RtMask) >> 16; // bits 20:16
        rd = (instructionWord & RTypeInstruction::RdMask) >> 11; // bits 15:11
        immediate = (instructionWord & ITypeInstruction::ImmediateMask); // bits 15:0
        funct = (instructionWord & RTypeInstruction::FunctMask); // bits 5:0

        success &= regMem.getRegister(rs, reg1Data);
        success &= regMem.getRegister(rt, reg2Data);

        ControlUnit::evaluate(instructionWord, regDest, branch, memRead, memToReg, aluOp,
                                                memWrite, aluSrc, regWrite);

        // take in ALU op and then overwrite it
        ControlUnit::aluControlUnit(funct, aluOp, aluOp);

        signExtendImm = MIPSUtils::signExtend(immediate);


        alu.setOpCode(aluOp); // Set ALU opcode from control unit signals
        aluResult = alu.evaluate(reg1Data, MIPSUtils::mux(reg2Data, signExtendImm, aluSrc),
                                aluZeroFlag, aluOverflowFlag, aluCarryFlag);

        branchAluResult = branchAlu.evaluate(pcAdderResult, (signExtendImm << 2), 
                                            branchAluZero, branchAluOverflow, branchAluCarry);


        
        success &= dataMem.getRegister(memRead, aluResult, dataReadValue);
        
        success &= regMem.setRegister(regWrite, rd, MIPSUtils::mux(aluResult, dataReadValue, memToReg));


        programCounter = MIPSUtils::mux(pcAdderResult, branchAluResult, (aluZeroFlag && branch));

        if (aluOverflowFlag || aluCarryFlag)
        {
            // handle the overflow somehow?
            std::cout<<"ALU overflow on instruction " << programCounter << std::endl;
        }


        if (!success)
        {
            // found an error, don't continue
            std::cout << "Error found on instruction " << programCounter << std::endl;
            break;
        }
    }

    
    return 0;
}