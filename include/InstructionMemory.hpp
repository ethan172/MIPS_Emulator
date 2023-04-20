#ifndef INSTRUCTION_MEMORY_HPP
#define INSTRUCTION_MEMORY_HPP

#include "Memory.hpp"

// Inherite from Memory such that Memory is using 32bit registers
class InstructionMemory : private virtual Memory<uint32_t>
{
private:
    const uint16_t m_MemorySize;
    uint16_t m_InstructionCount;

public:
    InstructionMemory();
    InstructionMemory(const uint16_t memSize);
    ~InstructionMemory();

    // adds an instruction to the end of the 
    bool addInstruction(const uint32_t instr);

    // Retrieves an instruction at idx and stores in entry
    // Returns true on success, false on failure
    bool fetchInstruction(const uint16_t idx, uint32_t& entry) const;

    
    uint16_t getInstructionCount() const;

};

#endif // INSTRUCTION_MEMORY_HPP