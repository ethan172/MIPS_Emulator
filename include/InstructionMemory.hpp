#ifndef INSTRUCTION_MEMORY_HPP
#define INSTRUCTION_MEMORY_HPP

#include "Memory.hpp"
#include <cstdint>

// Inherite from Memory such that Memory is using 32bit registers
class InstructionMemory : private Memory<uint32_t>
{
private:
    uint16_t m_InstructionCount;

public:
    InstructionMemory();
    InstructionMemory(const uint16_t memSize);
    ~InstructionMemory();

    // adds an instruction to the end of the 
    bool addInstruction(const uint32_t instr);

    // Retrieves an instruction at idx and stores in entry
    // Returns true on success, false on failure
    bool getInstruction(const uint16_t idx, uint32_t& entry) const;

    // TODO
    bool parseInstruction(uint16_t startBit, uint16_t stopBit, uint16_t& result);

};

#endif // INSTRUCTION_MEMORY_HPP