#ifndef REGISTER_MEMORY_HPP
#define REGISTER_MEMORY_HPP

#include <cstdint>
#include "Memory.hpp"

class RegisterMemory : public Memory<uint32_t>
{
private:

public:
    RegisterMemory();

    ~RegisterMemory();

};

#endif // REGISTER_MEMORY_HPP