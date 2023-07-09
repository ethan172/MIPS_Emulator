#ifndef MIPS_PROCESSOR
#define MIPS_PROCESSOR

// #include "ALU.hpp"
#include "InstructionMemory.hpp"
#include "RegisterMemory.hpp"
#include "DataMemory.hpp"
#include <string>
#include <vector>

class MIPSProcessor
{
private:
    std::string m_InstructionFile;
    InstructionMemory m_InstructionMem; // should set size to 8192
    RegisterMemory m_RegMem; // should set size to 32
    DataMemory m_DataMem; // set to 4096

    uint32_t m_ProgramCounter;

public:
    MIPSProcessor();
    MIPSProcessor(std::string instFile);

    ~MIPSProcessor();

    void setInstructionBuffer(const std::string& instructionFile);
    void setInstructionBuffer(const std::vector<uint32_t>& instructions);

    void main();

    uint32_t* getDataMem() const;
    uint32_t* getRegMem() const;

};

#endif // MIPS_PROCESSOR