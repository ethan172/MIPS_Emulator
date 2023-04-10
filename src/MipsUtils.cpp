#include "MipsUtils.hpp"


uint16_t controlUnit(uint32_t opCode)
{
    uint16_t result = 0x0;

    /*
    Based on the instruction opcode craft the control unit output signal using appropriate masks
    the alu opcode needs to be retreived then aligned to the correct bits within the output signal
    */
    switch (opCode)
    {
        case OpCodes::instAdd:
            result = ControlSignals::REG_DST_MASK | ControlSignals::REG_WRITE_MASK | (ALUOpCodes::aluAdd << ControlSignals::aluLSB);
            break;
        
        case OpCodes::instSub:
            result = ControlSignals::REG_DST_MASK | ControlSignals::REG_WRITE_MASK | (ALUOpCodes::aluSub << ControlSignals::aluLSB);
            break;

        case OpCodes::instAnd:
            result = ControlSignals::REG_DST_MASK | ControlSignals::REG_WRITE_MASK | (ALUOpCodes::aluAnd << ControlSignals::aluLSB);
            break;

        case OpCodes::instOr:
            result = ControlSignals::REG_DST_MASK | ControlSignals::REG_WRITE_MASK | (ALUOpCodes::aluOr << ControlSignals::aluLSB);
            break;
        
        case OpCodes::instSlt:
            result = ControlSignals::REG_DST_MASK | ControlSignals::REG_WRITE_MASK | (ALUOpCodes::aluSlt << ControlSignals::aluLSB);
            break;

        case OpCodes::instLw:
            // ALU operation same as in add
            result = ControlSignals::REG_WRITE_MASK | ControlSignals::ALU_SRC_MASK | (ALUOpCodes::aluAdd << ControlSignals::aluLSB) | ControlSignals::MEM_TO_REG_MASK;
            break;
        
        case OpCodes::instSw:
            // ALU operation same as in add
            result = ControlSignals::ALU_SRC_MASK | (ALUOpCodes::aluAdd << ControlSignals::aluLSB) | ControlSignals::MEM_WRITE_MASK;
            break;
        
        case OpCodes::instBeq:
            // ALU operation same as in sub
            result = (ALUOpCodes::aluSub << ControlSignals::aluLSB);
            break;
    }

    return result;
}

uint32_t fullAdder(uint32_t lhs, uint32_t rhs)
{
    return (lhs + rhs);
}

uint16_t logicalAND(uint16_t lhs, uint16_t rhs)
{
    return (lhs & rhs);
}


uint16_t mux(uint16_t option0, uint16_t option1, bool select)
{
    return select ? option1 : option0;
}

/*
brief takes in a 16bit value and extends the sign
        such that the result is a 32 bit value

param val 16 bit input value to sign extend
*/
uint32_t signExtend(uint16_t val)
{

    // get the sign then throw it to the LSB
    // multiply that with 0xFFFF to get either all 1s or all 0s
    // shift it up to the 16 MSBs
    // set val to lower 16 bits
    return (uint32_t)((((0x8000 & val) >> 15) * 0xFFFF) << 16) | val;

}

