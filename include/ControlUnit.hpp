#ifndef CONTROL_UNIT_HPP
#define CONTROL_UNIT_HPP

#include <cstdint>

class ControlUnit
{
private:

public:

    // Parses out the instruction word and sets appropriate control signals
    void evaluate(const uint32_t instructionWord, bool& regDest, bool& branch, bool& memRead,
                    bool& memToReg, uint8_t& aluOp, bool& memWrite, bool& aluSrc, bool& regWrite);
};

namespace ControlSignals
{
    // bitmasks for signals coming out of the Control Unit
    const uint32_t REG_DST_MASK       = 0x001;
    const uint32_t BRANCH_MASK        = 0x002;
    const uint32_t MEM_READ_MASK      = 0x004;
    const uint32_t MEM_TO_REG_MASK    = 0x008;
    const uint32_t ALU_OP_MASK        = 0x070; // 3 bits
    const uint32_t MEM_WRITE_MASK     = 0x080;
    const uint32_t ALU_SRC_MASK       = 0x100;
    const uint32_t REG_WRITE_MASK     = 0x200;

    // LSB of the ALU op code within the control unit
    // This value will be the number of times the 
    // alu opcode is shifted when crafting the control unit output signal
    const uint16_t aluLSB = 4;
}

#endif // CONTROL_UNIT_HPP