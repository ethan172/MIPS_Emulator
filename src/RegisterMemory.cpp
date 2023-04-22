#include "RegisterMemory.hpp"


RegisterMemory::RegisterMemory() :
    Memory(64)
{
    
}

RegisterMemory::RegisterMemory(const uint16_t memSize) :
    Memory(memSize)
{

}

RegisterMemory::~RegisterMemory()
{
    
}

bool RegisterMemory::getRegister(const uint16_t idx, uint32_t &data) const
{
    return readRegister(idx, data);
}

bool RegisterMemory::setRegister(const bool regWrite, const uint16_t idx, const uint32_t data)
{
    // idx is within bounds and regWrite flag is true
    if (regWrite)
    {
        return writeRegister(idx, data);
    }

    return false;
}

void RegisterMemory::clearRegisters()
{
    clearMemory();
}
