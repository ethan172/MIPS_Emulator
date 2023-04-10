#include "InstructionMemory.hpp"

InstructionMemory::InstructionMemory()
{
    m_ProgramCounter = 0;
    m_InstructionCount = 0;
}

InstructionMemory::~InstructionMemory()
{
    
}

bool InstructionMemory::addInstruction(const uint32_t instr)
{
    bool retVal = writeRegister(instr, m_InstructionCount);
    
    if (retVal)
    {
        m_InstructionCount++;
        return true;
    }
    else
    {
        return false;
    }
}

bool InstructionMemory::removeInstruction(const uint16_t idx)
{
    // TODO
    bool retVal = false;

    return retVal;
}

bool InstructionMemory::parseInstruction(uint16_t startBit, uint16_t stopBit, uint16_t& result)
{
    return true;
}

void InstructionMemory::setProgramCounter(const uint16_t val)
{
    m_ProgramCounter = val;
}

uint16_t InstructionMemory::getProgramCounter() const
{
    return m_ProgramCounter;
}

void InstructionMemory::incrementProgramCounter()
{
    m_ProgramCounter++;
}

bool InstructionMemory::getInstruction(const uint16_t idx, uint32_t& entry) const
{
    return getRegister(idx, entry);
}
