#include "InstructionMemory.hpp"

InstructionMemory::InstructionMemory() :
    m_MemorySize(512),
    Memory(m_MemorySize)
{
    m_InstructionCount = 0;
}

InstructionMemory::InstructionMemory(const uint16_t memSize) :
    m_MemorySize(memSize),
    Memory(memSize)
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

    return getRegister(idx, entry);
}


uint16_t InstructionMemory::getInstructionCount() const
{
    return m_InstructionCount;
}