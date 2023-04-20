#include "ControlUnit.hpp"
#include "InstructionTypes.hpp"
#include "ALU.hpp"

#include <stdexcept>

namespace ControlUnit
{
    void evaluate(const uint32_t instructionWord, bool &regDest, bool &branch,
                                bool &memRead, bool &memToReg, uint8_t &aluOp, bool &memWrite, 
                                bool &aluSrc, bool &regWrite)
    {
        uint8_t opCode = (instructionWord & RTypeInstruction::OpCodeMask) >> 26;

        switch (opCode)
        {
            case OpCodes::ZERO:
                // R Type Instruction
                regDest = true;
                branch = false;
                memRead = false;
                memToReg = false;
                aluOp = instructionWord & RTypeInstruction::FunctMask; // TODO this probs isn't right
                memWrite = false;
                aluSrc = false;
                regWrite = true;
                break;
            
            case OpCodes::ADDI:
                // Add Immediate
                regDest = false;
                branch = false;
                aluSrc = true;
                memRead = false;
                memToReg = false;
                aluOp = ALU::ALUOpCodes::And;
                memWrite = false;
                aluSrc = false;
                regWrite = true;
                break;
            
            case OpCodes::ADDIU:
                // Add Immediate Unsigned
                regDest = false;
                branch = false;
                memRead = false;
                memToReg = false;
                aluOp = ALU::ALUOpCodes::Add;
                memWrite = false;
                aluSrc = false;
                regWrite = true;
                break;
            
            case OpCodes::ANDI:
                // And Immediate
                regDest = false;
                branch = false;
                memRead = false;
                memToReg = false;
                aluOp = ALU::ALUOpCodes::And;
                memWrite = false;
                aluSrc = false;
                regWrite = true;
                break;
            
            case OpCodes::BEQ:
                // Branch on equal
                regDest = false;
                branch = true;
                memRead = false;
                memToReg = false;
                aluOp = ALU::ALUOpCodes::Sub;
                memWrite = false;
                aluSrc = false;
                regWrite = false;
                break;
            
            case OpCodes::BNE:
                // Branch on not equal
                regDest = false;
                branch = true;
                memRead = false;
                memToReg = false;
                aluOp = ALU::ALUOpCodes::Sub;
                memWrite = false;
                aluSrc = false;
                regWrite = false;
                break;
            
            case OpCodes::J:
                // Jump
                regDest = false;
                branch = false; // TODO should this be true ??
                memRead = false;
                memToReg = false;
                aluOp = ALU::ALUOpCodes::Add; // This operation needs to result in 0
                memWrite = false;
                aluSrc = false;
                regWrite = false;
                break;
            
            case OpCodes::JAL:
                // Jump and Link 
                regDest = false;
                branch = false; // TODO should this be true ??
                memRead = false;
                memToReg = false;
                aluOp = ALU::ALUOpCodes::Add; // Same comment as Jump instruction
                memWrite = false;
                aluSrc = false;
                regWrite = true;
                break;
            
            case OpCodes::LBU:
                // Load byte unsigned
                regDest = false;
                branch = false;
                memRead = true;
                memToReg = true;
                aluOp = ALU::ALUOpCodes::Add;
                memWrite = false;
                aluSrc = false;
                regWrite = true;
                break;
            
            case OpCodes::LHU:
                // Load halfword unsigned
                regDest = false;
                branch = false;
                memRead = true;
                memToReg = true;
                aluOp = ALU::ALUOpCodes::Add;
                memWrite = false;
                aluSrc = false;
                regWrite = true;
                break;
            
            case OpCodes::LL:
                // Load linked
                regDest = false;
                branch = false;
                memRead = true;
                memToReg = true;
                aluOp = ALU::ALUOpCodes::Add;
                memWrite = false;
                aluSrc = false;
                regWrite = true;
                break;
            
            case OpCodes::LUI:
                // Load upper immediate
                regDest = false;
                branch = false;
                memRead = false;
                memToReg = true;
                aluOp = ALU::ALUOpCodes::Add;
                memWrite = false;
                aluSrc = false;
                regWrite = true;
                break;
            
            case OpCodes::LW:
                // Load Word
                regDest = false;
                branch = false;
                memRead = true;
                memToReg = true;
                aluOp = ALU::ALUOpCodes::Add;
                memWrite = false;
                aluSrc = false;
                regWrite = true;
                break;
            
            case OpCodes::ORI:
                // Or Immediate
                regDest = false;
                branch = false;
                memRead = false;
                memToReg = false;
                aluOp = ALU::ALUOpCodes::Or;
                memWrite = false;
                aluSrc = false;
                regWrite = true;
                break;
            
            case OpCodes::SLTI:
                // Set less than immediate
                regDest = false;
                branch = false;
                memRead = false;
                memToReg = false;
                aluOp = ALU::ALUOpCodes::Slt;
                memWrite = false;
                aluSrc = false;
                regWrite = true;
                break;
            
            case OpCodes::SLTIU:
                // Set less than immediate unsigned
                regDest = false;
                branch = false;
                memRead = false;
                memToReg = false;
                memWrite = false;
                aluOp = ALU::ALUOpCodes::Slt;
                memWrite = false;
                aluSrc = false;
                regWrite = true;
                break;
            
            case OpCodes::SB:
                // Store byte
                regDest = false;
                branch = false;
                memRead = false;
                memToReg = false;
                aluOp = ALU::ALUOpCodes::Add;
                memWrite = true;
                aluSrc = false;
                regWrite = false;
                break;
            
            case OpCodes::SC:
                // Store conditional
                regDest = false;
                branch = false;
                memRead = false;
                memToReg = false;
                aluOp = ALU::ALUOpCodes::Add;
                memWrite = true;
                aluSrc = false;
                regWrite = false;
                break;
            
            case OpCodes::SH:
                // Store halfword
                regDest = false;
                branch = false;
                memRead = false;
                memToReg = false;
                aluOp = ALU::ALUOpCodes::Add;
                memWrite = true;
                aluSrc = false;
                regWrite = false;
                break;
            
            case OpCodes::SW:
                // Store word
                regDest = false;
                branch = false;
                memRead = false;
                memToReg = true;
                aluOp = ALU::ALUOpCodes::Add;
                memWrite = true;
                aluSrc = false;
                regWrite = false;
                break;
            
            default:
                throw std::logic_error("Invalid opcode 0x" + std::to_string(opCode));
                break;
        }
    }
}