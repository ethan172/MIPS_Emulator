#ifndef DATA_MEMORY_HPP
#define DATA_MEMORY_HPP

#include "Memory.hpp"

class DataMemory : public Memory<uint32_t>
{
public:
    DataMemory();

    DataMemory(const uint16_t memSize);
    
    ~DataMemory();

    bool getRegister(const bool memRead, const uint16_t idx, uint32_t& data);

    bool setRegister(const bool memWrite, const uint16_t idx, const uint32_t data);

};

#endif // DATA_MEMORY_HPP