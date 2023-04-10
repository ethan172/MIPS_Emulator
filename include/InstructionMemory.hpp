#ifndef INSTRUCTION_MEMORY_HPP
#define INSTRUCTION_MEMORY_HPP

#include "Memory.hpp"
#include <cstdint>

// Inherite from Memory such that Memory is using 32bit registers
class InstructionMemory : private Memory<uint32_t>
{
private:
    uint16_t m_ProgramCounter;
    uint16_t m_InstructionCount;

public:
    InstructionMemory();
    InstructionMemory(const uint16_t memSize);
    ~InstructionMemory();

    // adds an instruction to the end of the 
    bool addInstruction(const uint32_t instr);

    bool addInstructions(); // TODO

    // Retrieves an instruction at idx and stores in entry
    // Returns true on success, false on failure
    bool getInstruction(const uint16_t idx, uint32_t& entry) const;

    // removes an instruction at the specified idx
    bool removeInstruction(const uint16_t idx);

    bool parseInstruction(uint16_t startBit, uint16_t stopBit, uint16_t& result);

    // will set m_ProgramCounter to given value
    // no bounds checking is done here
    void setProgramCounter(const uint16_t val);

    // returns value of m_ProgramCounter
    uint16_t getProgramCounter() const;

    // Increments the program counter
    void incrementProgramCounter();

};

#endif // INSTRUCTION_MEMORY_HPP