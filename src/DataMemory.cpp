#include "DataMemory.hpp"


DataMemory::DataMemory() :
    Memory(4096),
    m_MemorySize(getMemorySize())
{

}

DataMemory::DataMemory(const uint16_t memSize) :
    Memory(memSize),
    m_MemorySize(memSize)
{

}

DataMemory::~DataMemory()
{

}

bool DataMemory::getRegister(const bool memRead, const uint16_t idx, uint32_t &data)
{
    if (memRead && idx < m_MemorySize)
    {
        return readRegister(idx, data);
    }

    return false;
}

bool DataMemory::setRegister(const bool memWrite, const uint16_t idx, const uint32_t data)
{
    if (memWrite && idx < m_MemorySize)
    {
        return writeRegister(idx, data);
    }

    return false;
}