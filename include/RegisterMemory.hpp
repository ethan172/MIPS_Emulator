#ifndef REGISTER_MEMORY_HPP
#define REGISTER_MEMORY_HPP

#include <cstdint>
#include "Memory.hpp"

class RegisterMemory : private virtual Memory<uint32_t>
{
private:
    const uint16_t m_MemorySize;

public:
    RegisterMemory();

    RegisterMemory(const uint16_t memSize);

    ~RegisterMemory();

    /*
    \brief Reads a register value

    @param [in] idx Index/register to read
    @param [out] data Value within the register being read

    \return True if idx is valid, false if idx is invalid
    */
    bool readRegister(const uint16_t idx, uint32_t& data) const;

    /*
    \brief Writes a value to a register

    @param [in] idx Index/register to write
    @param [in] data Value to write to the register

    \return True if idx is valid, false if idx is invalid
    */
    bool writeRegister(const uint16_t idx, const uint32_t data);

};

#endif // REGISTER_MEMORY_HPP