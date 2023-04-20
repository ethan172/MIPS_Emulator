#ifndef INSTRUCTION_TYPES_HPP
#define INSTRUCTION_TYPES_HPP

#include <cstdint>

namespace RTypeInstruction
{
    const uint32_t OpCodeMask   = 0xFC000000; // bits 31:26
    const uint32_t RsMask       = 0x03E00000; // bits 25:21
    const uint32_t RtMask       = 0x001F0000; // bits 20:16
    const uint32_t RdMask       = 0x0000F800; // bits 15:11
    const uint32_t ShamtMask    = 0x000007C0; // bits 10:6
    const uint32_t FunctMask    = 0x0000003F; // bits 5:0
}

namespace ITypeInstruction
{
    const uint32_t OpCodeMask       = 0xFC000000; // bits 31:26
    const uint32_t RsMask           = 0x03E00000; // bits 25:21
    const uint32_t RtMask           = 0x001F0000; // bits 20:16
    const uint32_t ImmediateMask    = 0x00007FFF; // bits 15:0
}

namespace JTypeInstruction
{
    const uint32_t OpCodeMask       = 0xFC000000; // bits 31:26
    const uint32_t AddressMask      = 0x01FFFFFF; // bits 25:0
}

enum OpCodes
{
    ZERO = 0,
    ADDI = 0x8,
    ADDIU = 0x9,
    ANDI = 0xC,
    BEQ = 0x4,
    BNE = 0x5,
    J = 0x2,
    JAL = 0x3,
    LBU = 0x24,
    LHU = 0x25,
    LL = 0x30,
    LUI = 0xF,
    LW = 0x23,
    ORI = 0xD,
    SLTI = 0xA,
    SLTIU = 0xB,
    SB = 0x28,
    SC = 0x38,
    SH = 0X29,
    SW = 0x2B
};

enum FunctCodes
{
    ADD     = 0x20,
    ADDU    = 0x21,
    AND     = 0x24,
    JR      = 0x8,
    NOR     = 0x27,
    OR      = 0x25,
    SLT     = 0x2A,
    SLTU    = 0x2B,
    SLL     = 0x0,
    SRL     = 0x2,
    SUB     = 0x22,
    SUBU    = 0x23
};


#endif // INSTRUCTION_TYPES_HPP