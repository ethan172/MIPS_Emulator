#ifndef ALU_HPP
#define ALU_HPP

#include <cstdint>

class ALU
{
private:
    uint16_t m_AluOp;
    uint32_t m_LhsOperand;
    uint32_t m_RhsOperand;

    // performs respective arithmetic operation
    // on m_LhsOperand and m_RhsOperand 
    uint32_t aluAdd() const;
    uint32_t aluSub() const;
    uint32_t aluAnd() const;
    uint32_t aluOr() const;
    uint32_t aluSlt() const;

public:

    ALU();
    ~ALU();

    void setAluOp(uint16_t aluOp);

    uint16_t getAluOp() const;

    void setLhsOperand(uint32_t lhs);
    void setRhsOperand(uint32_t rhs);

    bool evaluate(bool& zeroOut, uint32_t& result) const;

};

#endif // ALU_HPP