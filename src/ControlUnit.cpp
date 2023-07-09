#include "ControlUnit.hpp"
#include "InstructionTypes.hpp"
#include "ALU.hpp"

#include <stdexcept>
#include <iostream>

namespace ControlUnit
{
    uint16_t evaluate(const uint32_t instructionWord)
    {
        uint8_t opCode = (instructionWord & RTypeInstruction::OpCodeMask) >> 26;

        uint16_t controlSignals = 0x0;
        uint16_t aluOp;

        switch (opCode)
        {
            case OpCodes::ZERO:
                // R Type Instruction
                controlSignals |= ControlSignals::REG_DST_MASK;
                aluOp = ALUOpFromFunct((instructionWord & RTypeInstruction::FunctMask));
                controlSignals |= ControlSignals::REG_WRITE_MASK;
                break;
            
            case OpCodes::ADDI:
                // Add Immediate
                controlSignals |= ControlSignals::ALU_SRC_MASK;
                
                aluOp = ALU::ALUOpCodes::Add;
                
                controlSignals |= ControlSignals::REG_WRITE_MASK;
                break;
            
            case OpCodes::ADDIU:
                // Add Immediate Unsigned
                aluOp = ALU::ALUOpCodes::Add;
                controlSignals |= ControlSignals::ALU_SRC_MASK;
                controlSignals |= ControlSignals::REG_WRITE_MASK;
                break;
            
            case OpCodes::ANDI:
                // And Immediate
                aluOp = ALU::ALUOpCodes::And;
                controlSignals |= ControlSignals::ALU_SRC_MASK;
                controlSignals |= ControlSignals::REG_WRITE_MASK;
                break;
            
            case OpCodes::BEQ:
                // Branch on equal
                controlSignals |= ControlSignals::BRANCH_MASK;
                aluOp = ALU::ALUOpCodes::Sub;
                break;
            
            case OpCodes::BNE:
                // Branch on not equal
                controlSignals |= ControlSignals::BRANCH_MASK;
                aluOp = ALU::ALUOpCodes::Sub;
                break;
            
            case OpCodes::J:
                // Jump
                controlSignals |= ControlSignals::JUMP_MASK;
                aluOp = ALU::ALUOpCodes::Sub; // Pretty sure this is a don't care
                break;
            
            case OpCodes::JAL:
                // Jump and Link 
                controlSignals |= ControlSignals::JUMP_MASK;
                aluOp = ALU::ALUOpCodes::Sub; // Same comment as Jump instruction
                controlSignals |= ControlSignals::REG_WRITE_MASK;
                break;
            
            case OpCodes::LBU:
                // Load byte unsigned
                controlSignals |= ControlSignals::MEM_READ_MASK;
                controlSignals |= ControlSignals::MEM_TO_REG_MASK;

                aluOp = ALU::ALUOpCodes::Add;
                controlSignals |= ControlSignals::REG_WRITE_MASK;
                break;
            
            case OpCodes::LHU:
                // Load halfword unsigned
                controlSignals |= ControlSignals::MEM_READ_MASK;
                controlSignals |= ControlSignals::MEM_TO_REG_MASK;
                aluOp = ALU::ALUOpCodes::Add;
                controlSignals |= ControlSignals::REG_WRITE_MASK;
                break;
            
            case OpCodes::LL:
                // Load linked
                controlSignals |= ControlSignals::MEM_READ_MASK;
                controlSignals |= ControlSignals::MEM_TO_REG_MASK;
                aluOp = ALU::ALUOpCodes::Add;
                controlSignals |= ControlSignals::REG_WRITE_MASK;
                break;
            
            case OpCodes::LUI:
                // Load upper immediate
                controlSignals |= ControlSignals::MEM_TO_REG_MASK;
                aluOp = ALU::ALUOpCodes::Add;
                controlSignals |= ControlSignals::ALU_SRC_MASK;
                controlSignals |= ControlSignals::REG_WRITE_MASK;
                break;
            
            case OpCodes::LW:
                // Load Word
                controlSignals |= ControlSignals::MEM_READ_MASK;
                controlSignals |= ControlSignals::MEM_TO_REG_MASK;
                aluOp = ALU::ALUOpCodes::Add;
                controlSignals |= ControlSignals::REG_WRITE_MASK;
                break;
            
            case OpCodes::ORI:
                // Or Immediate
                aluOp = ALU::ALUOpCodes::Or;
                controlSignals |= ControlSignals::ALU_SRC_MASK;
                controlSignals |= ControlSignals::REG_WRITE_MASK;
                break;
            
            case OpCodes::SLTI:
                // Set less than immediate
                aluOp = ALU::ALUOpCodes::Slt;
                controlSignals |= ControlSignals::ALU_SRC_MASK;
                controlSignals |= ControlSignals::REG_WRITE_MASK;
                break;
            
            case OpCodes::SLTIU:
                // Set less than immediate unsigned
                aluOp = ALU::ALUOpCodes::Slt;
                controlSignals |= ControlSignals::ALU_SRC_MASK;
                controlSignals |= ControlSignals::REG_WRITE_MASK;
                break;
            
            case OpCodes::SB:
                // Store byte
                aluOp = ALU::ALUOpCodes::Add;
                controlSignals |= ControlSignals::MEM_WRITE_MASK;
                break;
            
            case OpCodes::SC:
                // Store conditional
                aluOp = ALU::ALUOpCodes::Add;
                controlSignals |= ControlSignals::MEM_WRITE_MASK;
                break;
            
            case OpCodes::SH:
                // Store halfword
                aluOp = ALU::ALUOpCodes::Add;
                controlSignals |= ControlSignals::MEM_WRITE_MASK;
                break;
            
            case OpCodes::SW:
                // Store word
                controlSignals |= ControlSignals::MEM_TO_REG_MASK;
                aluOp = ALU::ALUOpCodes::Add;
                controlSignals |= ControlSignals::MEM_WRITE_MASK;
                break;
            
            default:
                std::cout << "Invalid opcode: " << std::uppercase << std::hex << opCode << std::endl;
                break;
            
        }

        controlSignals |= (aluOp << ControlSignals::AluOpLSB);
        return controlSignals;
    }

    
    uint16_t ALUOpFromFunct(const uint8_t funct)
    {
        uint16_t aluControl = 0;

        switch (funct)
        {
            case FunctCodes::SLL:
                // Shift left logical
                aluControl = ALU::ALUOpCodes::Sll;
                break;
            
            case FunctCodes::SRL:
                // Shift right logical
                aluControl = ALU::ALUOpCodes::Srl;
                break;

            case FunctCodes::JR:
                // Jump register
                aluControl = ALU::ALUOpCodes::Sub; // pretty sure this is a don't care
                break;
            
            case FunctCodes::ADD:
                // Add
                aluControl = ALU::ALUOpCodes::Add;
                break;
            
            case FunctCodes::ADDU:
                // Add unsigned
                aluControl = ALU::ALUOpCodes::Add; // TODO does this need to be different for unsigned?
                break;

            case FunctCodes::SUB:
                // Subtraction
                aluControl = ALU::ALUOpCodes::Sub;
                break;
            
            case FunctCodes::SUBU:
                // Sub unsigned
                aluControl = ALU::ALUOpCodes::Sub; // TODO does this need to be different for unsigned?
                break;
            
            case FunctCodes::AND:
                // And
                aluControl = ALU::ALUOpCodes::And;
                break;
            
            case FunctCodes::OR:
                // Or
                aluControl = ALU::ALUOpCodes::Or;
                break;
            
            case FunctCodes::NOR:
                // Nor
                aluControl = ALU::ALUOpCodes::Nor;
                break;
            
            case FunctCodes::SLT:
                // Set less than
                aluControl = ALU::ALUOpCodes::Slt;
                break;

            case FunctCodes::SLTU:
                // Set less than unsigned
                aluControl = ALU::ALUOpCodes::Slt; // TODO does this need to be different for unsigned?
                break;
            
            default:
                std::cout << "Could not compute ALU opcode from funct ";
                std::cout << std::uppercase << std::hex << funct << std::endl;
                break;
        }

        return aluControl;
    }
}