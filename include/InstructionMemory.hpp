#ifndef INSTRUCTION_MEMORY_HPP
#define INSTRUCTION_MEMORY_HPP


#include <cstdint>

class InstructionMemory
{
private:
    uint16_t m_BufferSize;
    uint32_t *m_MemoryBuffer; // TODO does this really need to be dynamic?

public:
    InstructionMemory();
    ~InstructionMemory();

};

#endif // INSTRUCTION_MEMORY_HPP