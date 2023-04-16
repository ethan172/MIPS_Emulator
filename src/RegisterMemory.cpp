#include "RegisterMemory.hpp"


RegisterMemory::RegisterMemory() :
    m_MemorySize(64),
    Memory(m_MemorySize)
{
    
}

RegisterMemory::RegisterMemory(const uint16_t memSize) :
    m_MemorySize(memSize),
    Memory(memSize)
{

}

RegisterMemory::~RegisterMemory()
{
    
}

bool RegisterMemory::readRegister(const uint16_t idx, uint32_t &data) const
{
    if (idx >= m_MemorySize)
    {
        return false;
    }

    return getRegister(idx, data);
}

bool RegisterMemory::writeRegister(const uint16_t idx, const uint32_t data)
{
    if (idx >= m_MemorySize)
    {
        return false;
    }

    return writeRegister(idx, data);
}
