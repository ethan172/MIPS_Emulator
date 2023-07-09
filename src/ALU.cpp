#include "ALU.hpp"
#include "MipsUtils.hpp"

#include <iostream>

ALU::ALU()
{
    m_OpCode = 0x0;
}

ALU::~ALU()
{

}

void ALU::setOpCode(uint16_t aluOp)
{
    m_OpCode = aluOp;
}

uint16_t ALU::getAluOp() const
{
    return m_OpCode;
}

uint32_t ALU::evaluate(const uint32_t lhs, const uint32_t rhs, bool& zeroFlag, bool& overflow, bool& carryOut)
{
    uint32_t result;

    // Perform opeartion based on alu opcode member
    switch (m_OpCode)
    {
        case ALUOpCodes::And:
            result = logicalAnd(lhs, rhs);
            break;
        
        case ALUOpCodes::Or:
            result = logicalOr(lhs, rhs);
            break;
        
        case ALUOpCodes::Add:
            result = add(lhs, rhs);
            break;
        
        case ALUOpCodes::Sll:
            result = sll(lhs, rhs);
            break;
            
        case ALUOpCodes::Srl:
            result = srl(lhs, rhs);
            break;
        
        case ALUOpCodes::Nor:
            result = nor(lhs, rhs);
            break;

        case ALUOpCodes::Sub:
            result = sub(lhs, rhs);
            break;        
        
        case ALUOpCodes::Slt:
            result = slt(lhs, rhs);
            break;
        
        default:
            std::cout << "Invalid ALU opcode 0x" << std::uppercase << std::hex << m_OpCode << std::endl;
            result = 0x0;
            break;
    }

    zeroFlag = m_ZeroFlag;
    overflow = m_Overflow;
    carryOut = m_CarryOut;

    return result;
}


int32_t ALU::add(const int32_t lhs, const int32_t rhs)
{
    int32_t result = lhs + rhs;

    // if both operands have the same sign and the result has a different sign
    // then overflow has occurred
    if (result > 0)
    {
        if (lhs < 0 && rhs < 0)
        {
            m_Overflow = true;
            m_CarryOut = true;
        }
        else
        {
            m_Overflow = false;
            m_CarryOut = false;
        }
    }
    else if (result < 0)
    {
        if (lhs > 0 && rhs > 0)
        {
            m_Overflow = true;
            m_CarryOut = true;
        }
        else
        {
            m_Overflow = false;
            m_CarryOut = false;
        }
    }
    else // result == 0
    {
        m_Overflow = false;
        m_CarryOut = false;
    }

    m_ZeroFlag = (result == 0);

    return result;
}

int32_t ALU::sub(const int32_t lhs, const int32_t rhs)
{
    // Subtraction is just fancy addition
    int32_t result = add(lhs, -rhs);

    return result;
}

uint32_t ALU::logicalOr(const uint32_t lhs, const uint32_t rhs)
{
    uint32_t result = lhs | rhs;
    m_ZeroFlag = (result == 0);
    m_Overflow = false;
    m_CarryOut = false;

    return result;
}

uint32_t ALU::logicalAnd(const uint32_t lhs, const uint32_t rhs)
{
    uint32_t result = lhs & rhs;
    m_ZeroFlag = (result == 0);
    m_Overflow = false;
    m_CarryOut = false;

    return result;
}

uint32_t ALU::slt(const int32_t lhs, const int32_t rhs)
{
    // slt = set less than
    // Return 1 if lhs < rhs, else return 0

    uint32_t result = (lhs < rhs);

    m_ZeroFlag = (result == 0);
    m_Overflow = false;
    m_CarryOut = false;

    return result;
}

uint32_t ALU::nor(const uint32_t lhs, const uint32_t rhs)
{
    uint32_t result = ~(lhs | rhs);

    m_ZeroFlag = (result == 0);
    m_Overflow = false;
    m_CarryOut = false;

    return result;
}

int32_t ALU::sll(const int32_t lhs, const int32_t rhs)
{
    int32_t result = (lhs << rhs);

    m_ZeroFlag = (result == 0);

    //shifting by rhs is the same as lhs * rhs
    m_Overflow = (result < rhs);
    m_CarryOut = false;

    return result;
}

int32_t ALU::srl(const int32_t lhs, const int32_t rhs)
{
    int32_t result = (lhs >> rhs);

    m_ZeroFlag = (result == 0);

    // Can't overflow on a right bit-shift
    m_Overflow = false;
    m_CarryOut = false;

    return result;
}