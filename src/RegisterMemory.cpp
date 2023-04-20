#include "RegisterMemory.hpp"


RegisterMemory::RegisterMemory() :
    Memory(64),
    m_MemorySize(getMemorySize())
{
    
}

RegisterMemory::RegisterMemory(const uint16_t memSize) :
    Memory(memSize),
    m_MemorySize(memSize)
{

}

RegisterMemory::~RegisterMemory()
{
    
}

bool RegisterMemory::getRegister(const uint16_t idx, uint32_t &data) const
{
    if (idx >= m_MemorySize)
    {
        return false;
    }

    return readRegister(idx, data);
}

bool RegisterMemory::setRegister(const bool regWrite, const uint16_t idx, const uint32_t data)
{
    // idx is within bounds and regWrite flag is true
    if (regWrite && idx < m_MemorySize)
    {
        return writeRegister(idx, data);
    }

    return false;
}
