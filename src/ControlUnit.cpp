#include "ControlUnit.hpp"

uint16_t controlUnit(uint32_t opCode)
{
    uint16_t result = 0x0;

    /*
    Based on the instruction opcode craft the control unit output signal using appropriate masks
    the alu opcode needs to be retreived then aligned to the correct bits within the output signal
    */

    /*
    switch (opCode)
    {
        case OpCodes::instAdd:
            result = ControlSignals::REG_DST_MASK | ControlSignals::REG_WRITE_MASK | (ALU::ALUOpCodes::Add << ControlSignals::aluLSB);
            break;
        
        case OpCodes::instSub:
            result = ControlSignals::REG_DST_MASK | ControlSignals::REG_WRITE_MASK | (ALU::ALUOpCodes::Sub << ControlSignals::aluLSB);
            break;

        case OpCodes::instAnd:
            result = ControlSignals::REG_DST_MASK | ControlSignals::REG_WRITE_MASK | (ALU::ALUOpCodes::And << ControlSignals::aluLSB);
            break;

        case OpCodes::instOr:
            result = ControlSignals::REG_DST_MASK | ControlSignals::REG_WRITE_MASK | (ALU::ALUOpCodes::Or << ControlSignals::aluLSB);
            break;
        
        case OpCodes::instSlt:
            result = ControlSignals::REG_DST_MASK | ControlSignals::REG_WRITE_MASK | (ALU::ALUOpCodes::Slt << ControlSignals::aluLSB);
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

    */

    return result;
}

void ControlUnit::evaluate(const uint32_t instructionWord, bool &regDest, bool &branch,
                            bool &memRead, bool &memToReg, uint8_t &aluOp, bool &memWrite, 
                            bool &aluSrc, bool &regWrite)
{
    // TODO
    return;
}
