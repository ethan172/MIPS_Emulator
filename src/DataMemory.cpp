#include "DataMemory.hpp"


DataMemory::DataMemory() :
    Memory(4096)
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

    return false;
}

bool DataMemory::setRegister(const bool memWrite, const uint16_t idx, const uint32_t data)
{
    if (memWrite)
    {
        return writeRegister(idx, data);
    }

    return false;
}