#ifndef MIPS_UTILS_HPP
#define MIPS_UTILS_HPP

#include <cstdint>

namespace OpCodes
{
    // Instruction Opcodes
    const uint16_t instAdd    = 0x1; // TODO
    const uint16_t instSub    = 0x2;
    const uint16_t instAnd    = 0x3;
    const uint16_t instOr     = 0x4;
    const uint16_t instSlt    = 0x5;
    const uint16_t instLw     = 0x6;
    const uint16_t instSw     = 0x7;
    const uint16_t instBeq    = 0x8;
}

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

namespace ALUOpCodes
{
    // Opcodes used specifically by the ALU
    const uint8_t aluAdd     = 0x0; // TODO
    const uint8_t aluSub     = 0x1;
    const uint8_t aluOr      = 0x2;
    const uint8_t aluAnd     = 0x3;
    const uint8_t aluSlt     = 0x4;
}

uint32_t fullAdder(uint32_t lhs, uint32_t rhs);
uint16_t logicalAND(uint16_t lhs, uint16_t rhs);
uint16_t mux(uint16_t option0, uint16_t option1, bool select);
uint32_t signExtend(uint16_t val);

#endif // MIPS_UTILS_HPP