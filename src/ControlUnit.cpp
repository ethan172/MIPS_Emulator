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
                aluOp = ALU::ALUOpType::Arithmetic;
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
                aluOp = ALU::ALUOpType::LoadStore;
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
                aluOp = ALU::ALUOpType::LoadStore;
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
                branch = true; // TODO should this be true ??
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
                branch = true; // TODO should this be true ??
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

    
    void aluControlUnit(const uint8_t funct, const uint8_t aluOpType, uint8_t &aluControl)
    {
        if ((aluOpType & 0x3) == ALU::ALUOpType::LoadStore)
        {
            aluControl = ALU::ALUOpCodes::Add;
        }
        else if ((aluOpType & 0x1) == ALU::ALUOpType::Branch)
        {
            aluControl = ALU::ALUOpCodes::Sub;
        }
        else if (aluOpType == ALU::ALUOpType::AddI)
        {
            aluControl = ALU::ALUOpCodes::Add;
        }
        else if (aluOpType == ALU::ALUOpType::AndI)
        {
            aluControl = ALU::ALUOpCodes::And;
        }
        else
        {
            switch (funct & RTypeInstruction::FunctMask)
            {
                case 0x0:
                    aluControl = ALU::ALUOpCodes::Add;
                    break;
                
                case 0x2:
                    aluControl = ALU::ALUOpCodes::Sub;
                    break;
                
                case 0x4:
                    aluControl = ALU::ALUOpCodes::And;
                    break;
                
                case 0x5:
                    aluControl = ALU::ALUOpCodes::Or;
                    break;
                
                case 0xA:
                    aluControl = ALU::ALUOpCodes::Slt;
                    break;
                
                default:
                    throw std::logic_error("Could not calculate ALU opcode from funct");
                    break;
            }
        }
    }
}