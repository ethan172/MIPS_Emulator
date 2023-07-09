#ifndef ALU_HPP
#define ALU_HPP

#include <cstdint>

class ALU
{
private:
    uint16_t m_OpCode; // opcode for the alu operation
    
    // Output flags for the ALU operation
    bool m_ZeroFlag;
    bool m_Overflow;
    bool m_CarryOut;

    // performs respective arithmetic operation
    // on m_LhsOperand and m_RhsOperand 
    int32_t add(const int32_t lhs, const int32_t rhs);
    int32_t sub(const int32_t lhs, const int32_t rhs);
    uint32_t logicalAnd(const uint32_t lhs, const uint32_t rhs);
    uint32_t logicalOr(const uint32_t lhs, const uint32_t rhs);
    uint32_t slt(const int32_t lhs, const int32_t rhs);
    uint32_t nor(const uint32_t lhs, const uint32_t rhs);
    int32_t sll(const int32_t lhs, const int32_t rhs);
    int32_t srl(const int32_t lhs, const int32_t rhs);

public:

    ALU();
    ~ALU();

    void setOpCode(uint16_t aluOp);

    uint16_t getAluOp() const;

    /*
    \brief Executes an operation on the ALU. Prerequisit is that the Opcode member must be set

    @param [in] lhs The left hand side operand
    @param [in] rhs The right hand side operand
    @param [out] zeroFlag True if the result is zero
    @param [out] overflow True if an overflow resulted from the operation
    @param [out] carryOut True if the arithmetic operation between two unsigned numbers has a carry out

    \return The result of the operation
    */
    uint32_t evaluate(const uint32_t lhs, const uint32_t rhs, bool& zeroFlag, bool& overflow, bool& carryOut);

    // Supposed to only have 3 bits for this - max value is 0x7
    enum ALUOpCodes
    {
        And     = 0x0,
        Or      = 0x1,
        Add     = 0x2,
        Sll     = 0x3,
        Srl     = 0x4,
        Nor     = 0x5,
        Sub     = 0x6,
        Slt     = 0x7
    };
};

#endif // ALU_HPP