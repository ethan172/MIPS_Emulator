#include "MIPSProcessor.hpp"
#include "InstructionTypes.hpp"
#include "MipsUtils.hpp"
#include "ControlUnit.hpp"

#include "ALU.hpp"

#include <fstream>


MIPSProcessor::MIPSProcessor() :
                m_InstructionMem(8192),
                m_RegMem(32),
                m_DataMem(4096)
{
    m_ProgramCounter = 0;
    m_InstructionFile = "";
}


MIPSProcessor::MIPSProcessor(std::string instFile) :
                m_InstructionMem(8192),
                m_RegMem(32),
                m_DataMem(4096)
{
    m_ProgramCounter = 0;
    m_InstructionFile = instFile;
}


MIPSProcessor::~MIPSProcessor()
{

}

void MIPSProcessor::setInstructionBuffer(const std::string& instructionFile)
{
    uint32_t lineNumber = 1;
    uint32_t instructionWord;
    bool success = true; // overall flag to detect an error

    std::ifstream inFile(instructionFile, std::fstream::in);
    inFile >> std::hex >> instructionWord; // prime
    while (!inFile.fail()) // test
    {
        success = m_InstructionMem.addInstruction(instructionWord);
        if (!success)
        {
            std::cout << "Could not add instruction " << lineNumber << std::endl;
        }
        
        lineNumber++;
        inFile >> std::hex >> instructionWord; // reprime
        success = true;
    }
}


void MIPSProcessor::setInstructionBuffer(const std::vector<uint32_t>& instructions)
{
    bool success = true;
    for (unsigned int i = 0; i < instructions.size(); i++)
    {
        success = m_InstructionMem.addInstruction(instructions[i]);
        if (!success)
        {
            std::cout << "Could not add instruction " << i+1 << std::endl;
        }
        
        success = true;
    }
}

void MIPSProcessor::main()
{
    // std::ifstream inFile(instructionFile, std::fstream::in);
    // uint32_t lineNumber = 1;
    uint32_t instructionWord;
    bool success = true; // overall flag to detect an error

    // Instruction memory object and supporting variables
    uint16_t rs, rt, rd, immediate;
    uint32_t signExtendImm;
    uint32_t jumpAddress;

    // inFile >> std::hex >> instructionWord; // prime
    // while (!inFile.fail()) // test
    // {
    //     success = m_InstructionMem.addInstruction(instructionWord);
    //     if (!success)
    //     {
    //         std::cout << "Could not add instruction " << lineNumber << std::endl;
    //     }
        
    //     lineNumber++;
    //     inFile >> std::hex >> instructionWord; // reprime
    // }


    uint32_t reg1Data, reg2Data;

    // full ALU between the register and data memory spaces + supporting variables
    ALU alu;
    bool aluZeroFlag, aluOverflowFlag, aluCarryFlag;
    uint32_t aluResult;
    

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
    

    uint16_t controlSignals;    

    while (m_ProgramCounter < m_InstructionMem.getInstructionCount())
    {
        std::cout << "Processing instruction " << m_ProgramCounter << std::endl;
        /*
        Diagram has PC + 4 but here it is PC + 1. This is because normally +4 will get you +4 bytes (32 bits)
        but since this MIPS Emulator implementation uses arrays we just need to add 1 to the index
        */
        pcAdderResult = pcAdder.evaluate(m_ProgramCounter, 1, pcAdderZero, pcAdderOverflow, pcAdderCarry);
        success &= m_InstructionMem.fetchInstruction(m_ProgramCounter, instructionWord);


        // Parse out different pieces of the instruction word
        rs = (instructionWord & RTypeInstruction::RsMask) >> 21; // bits 25:21
        rt = (instructionWord & RTypeInstruction::RtMask) >> 16; // bits 20:16
        rd = (instructionWord & RTypeInstruction::RdMask) >> 11; // bits 15:11
        immediate = (instructionWord & ITypeInstruction::ImmediateMask); // bits 15:0
        jumpAddress = (instructionWord & JTypeInstruction::AddressMask); // bits 25:0

        success &= m_RegMem.getRegister(rs, reg1Data);
        success &= m_RegMem.getRegister(rt, reg2Data);

        // This handles control unit and ALU control unit
        controlSignals = ControlUnit::evaluate(instructionWord);

        std::cout << "Control signals: " << std::uppercase << std::hex << "0x" << controlSignals << std::endl;
    

        signExtendImm = MIPSUtils::signExtend(immediate);

        // Set ALU opcode from control unit signals
        alu.setOpCode(((controlSignals & ControlUnit::ControlSignals::ALU_OP_MASK) >> ControlUnit::ControlSignals::AluOpLSB)); 
        aluResult = alu.evaluate(reg1Data, 
                                MIPSUtils::mux(reg2Data, signExtendImm, 
                                                (ControlUnit::ControlSignals::ALU_SRC_MASK & controlSignals)),
                                aluZeroFlag, aluOverflowFlag, aluCarryFlag);
        
        std::cout << "ALU Result: " << std::uppercase << std::hex << "0x" << aluResult << std::endl;
        std::cout << "ALU Zero: " << aluZeroFlag << std::endl;

        // Sign extend immediate is not shifted left 2 because just need to add 1 to array index
        branchAluResult = branchAlu.evaluate(pcAdderResult, signExtendImm,
                                            branchAluZero, branchAluOverflow, branchAluCarry);

        std::cout << "branchALUResult: " << branchAluResult << std::endl;

        
        success &= m_DataMem.getRegister((ControlUnit::ControlSignals::MEM_READ_MASK & controlSignals),
                                        aluResult, dataReadValue);

        if (!success)
        {
            std::cout << "data memory error" << std::endl;
        }

        success &= m_RegMem.setRegister((ControlUnit::ControlSignals::REG_WRITE_MASK & controlSignals),
                                    MIPSUtils::mux(rt, rd, (ControlUnit::ControlSignals::REG_DST_MASK & controlSignals)),
                                    MIPSUtils::mux(aluResult, 
                                                    dataReadValue, 
                                                    ControlUnit::ControlSignals::MEM_TO_REG_MASK & controlSignals));

        if (!success)
        {
            std::cout << "register memory error" << std::endl;
        }


        // branch mux
        m_ProgramCounter = MIPSUtils::mux(pcAdderResult, branchAluResult,
                                        (aluZeroFlag && (ControlUnit::ControlSignals::BRANCH_MASK & controlSignals)));

        // jump mux
        m_ProgramCounter = MIPSUtils::mux(m_ProgramCounter, jumpAddress, 
                                        (ControlUnit::ControlSignals::JUMP_MASK & controlSignals));

        if (m_ProgramCounter >= m_InstructionMem.getInstructionCount())
        {
            std::cout << "Program counter going out of bounds with value: " << m_ProgramCounter << std::endl;
        }
        else
        {
            std::cout << "Program counter set to " << m_ProgramCounter << std::endl;
        }


        if (aluOverflowFlag || aluCarryFlag)
        {
            // handle the overflow somehow?
            std::cout<<"ALU overflow on instruction " << m_ProgramCounter << std::endl;
        }


        if (!success)
        {
            // found an error, don't continue
            std::cout << "Error found on instruction " << m_ProgramCounter << std::endl;
            break;
        }
    }

    // m_DataMem.dumpMemory("DataMemoryDump.csv");
    // m_RegMem.dumpMemory("RegisterMemoryDump.csv");
}

uint32_t* MIPSProcessor::getDataMem() const
{
    return m_DataMem.getMemoryBuffer();
}

uint32_t* MIPSProcessor::getRegMem() const
{
    return m_RegMem.getMemoryBuffer();
}