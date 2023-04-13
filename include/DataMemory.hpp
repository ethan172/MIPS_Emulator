#ifndef DATA_MEMORY_HPP
#define DATA_MEMORY_HPP

#include <cstdint>
#include "Memory.hpp"

class DataMemory : Memory<uint32_t>
{
private:

public:
    DataMemory();
    ~DataMemory();

};

#endif // DATA_MEMORY_HPP