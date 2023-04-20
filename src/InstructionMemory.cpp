#include "InstructionMemory.hpp"

InstructionMemory::InstructionMemory() :
    Memory(512),
    m_MemorySize(getMemorySize())
{
    m_InstructionCount = 0;
}

InstructionMemory::InstructionMemory(const uint16_t memSize) :
    Memory(memSize),
    m_MemorySize(memSize)
{
    m_InstructionCount = 0;
}

InstructionMemory::~InstructionMemory()
{
    
}

bool InstructionMemory::addInstruction(const uint32_t instr)
{
    bool retVal = writeRegister(m_InstructionCount, instr);
    
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

bool InstructionMemory::fetchInstruction(const uint16_t idx, uint32_t& entry) const
{
    if (idx >= m_InstructionCount)
    {
        return false;
    }

    return readRegister(idx, entry);
}


uint16_t InstructionMemory::getInstructionCount() const
{
    return m_InstructionCount;
}