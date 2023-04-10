#include "ALU.hpp"
#include "MipsUtils.hpp"

ALU::ALU()
{
    m_AluOp = 0x0;
    m_LhsOperand = 0x0;
    m_RhsOperand = 0x0;
}

ALU::~ALU()
{

}

void ALU::setLhsOperand(uint32_t lhs)
{
    m_LhsOperand = lhs;
}

void ALU::setRhsOperand(uint32_t rhs)
{
    m_RhsOperand = rhs;
}

uint16_t ALU::getAluOp() const
{
    return m_AluOp;
}

bool ALU::evaluate(bool& zeroOut, uint32_t& result) const
{
    // Perform opeartion based on alu opcode member
    switch (m_AluOp)
    {
        case ALUOpCodes::aluAdd:
            result = aluAdd();
            break;

        case ALUOpCodes::aluSub:
            result = aluSub();
            break;
        
        case ALUOpCodes::aluOr:
            result = aluOr();
            break;
        
        case ALUOpCodes::aluAnd:
            result = aluAnd();
            break;
        
        case ALUOpCodes::aluSlt:
            result = aluSlt();
            break;
        
        default:
            result = 0x0;
            return false; // couldn't find the opcode so return fail
    }

    return true; // return success
}


uint32_t ALU::aluAdd() const
{
    return (m_LhsOperand + m_RhsOperand);
}

uint32_t ALU::aluSub() const
{
    return (m_LhsOperand - m_RhsOperand);
}

uint32_t ALU::aluOr() const
{
    return (m_LhsOperand | m_RhsOperand);
}

uint32_t ALU::aluAnd() const
{
    return (m_LhsOperand & m_RhsOperand);
}

uint32_t ALU::aluSlt() const
{
    // TODO
    return 0x0;
}