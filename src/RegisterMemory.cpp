#include "RegisterMemory.hpp"
#include <iostream>

void RegisterMemory::initializeMemory()
{
    writeRegister(0, 0);
}

RegisterMemory::RegisterMemory() :
    Memory(m_DefaultMemSize)
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
        // std::cout << "Writing register 0x" << std::uppercase << std::hex << idx;
        // std::cout << " with 0x" << std::uppercase << std::hex << data << std::endl;
        return writeRegister(idx, data);
    }

    return true;
}

void RegisterMemory::clearRegisters()
{
    clearMemory();
}
