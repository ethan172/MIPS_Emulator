#include "InstructionMemory.hpp"

InstructionMemory::InstructionMemory()
{
    m_InstructionCount = 0;
}

InstructionMemory::InstructionMemory(const uint16_t memSize) :
    Memory(memSize)
{
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

bool InstructionMemory::parseInstruction(uint16_t startBit, uint16_t stopBit, uint16_t& result)
{
    // TODO
    return true;
}

bool InstructionMemory::getInstruction(const uint16_t idx, uint32_t& entry) const
{
    return getRegister(idx, entry);
}
