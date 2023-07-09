#include "DataMemory.hpp"


DataMemory::DataMemory() :
    Memory(m_DefaultMemSize)
{

}

DataMemory::DataMemory(const uint16_t memSize) :
    Memory(memSize)
{

}

DataMemory::~DataMemory()
{

}

bool DataMemory::getRegister(const bool memRead, const uint16_t idx, uint32_t &data)
{
    if (memRead)
    {
        return readRegister(idx, data);
    }

    return true;
}

bool DataMemory::setRegister(const bool memWrite, const uint16_t idx, const uint32_t data)
{
    if (memWrite)
    {
        return writeRegister(idx, data);
    }

    return true;
}