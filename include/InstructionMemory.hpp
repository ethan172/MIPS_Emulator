#ifndef INSTRUCTION_MEMORY_HPP
#define INSTRUCTION_MEMORY_HPP

#include "Memory.hpp"

// Inherite from Memory such that Memory is using 32bit registers
class InstructionMemory : public Memory<uint32_t>
{
private:
    uint16_t m_InstructionCount;

public:
    InstructionMemory();
    InstructionMemory(const uint16_t memSize);
    ~InstructionMemory();

    /*
    \brief Writes an instruction to the next slot in the buffer if space available

    @param [in] instr Instruction to write

    \return True if space available, false otherwise
    */
    bool addInstruction(const uint32_t instr);

    /* 
    \brief Retrieves an instruction at idx and stores in entry

    @param [in] idx Address to fetch the instruction from
    @param [out] entry Value at the address

    \return true on success, false on failure
    */ 
    bool fetchInstruction(const uint16_t idx, uint32_t& entry) const;

    /*
    \brief Returns m_InstructionCount
    */
    uint16_t getInstructionCount() const;

};

#endif // INSTRUCTION_MEMORY_HPP