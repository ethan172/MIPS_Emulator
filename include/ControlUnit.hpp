#ifndef CONTROL_UNIT_HPP
#define CONTROL_UNIT_HPP

#include <cstdint>


namespace ControlUnit
{
    /*
    \brief Parses out the instruction word and sets appropriate control signals
    @param [in] instructionWord The 32bit instruction containing the opcode and all other
                fields within the particular instruction
    
    @param [out] regDest If True, 'write register' in register memory will be given the
                the Rd field from instructionWord. If false it will be given Rt field
    @param [out] branch True on a branch instruction, false on every other instruction
    @param [out] memRead If True, will read from data memory. If false, will not read from data memory
    @param [out] memToReg If True register memory will be written with value from data memory. If false
                            register memory will be written with result of ALU
    @param [out] aluOp Three bit opcode for the ALU operation to be executed
    @param [out] memWrite If true data memory will be read. If false data memory will not be read
    @param [out] aluSrc If true 2nd ALU operand will be the second register (Rt). If False the ALU operand
                        will be a sign extended immediate value from the instruction word
    @param [out] regWrite If true register data will be written. If false, it will not be

    \return None
    */
    uint16_t evaluate(const uint32_t instructionWord);
    
    /*
    \brief Generates appropriate ALU control signals

    @param [in] funct Five bit funct code from the instruction word

    \return ALU control signal
    */
    uint16_t ALUOpFromFunct(const uint8_t funct);


    /*
    Currently unused - either delete or rework how evaluate above works
    */
    namespace ControlSignals
    {
        // bitmasks for signals coming out of the Control Unit
        const uint32_t REG_DST_MASK       = 0x001; // bit 0
        const uint32_t BRANCH_MASK        = 0x002; // bit 1
        const uint32_t MEM_READ_MASK      = 0x004; // bit 2
        const uint32_t MEM_TO_REG_MASK    = 0x008; // bit 3
        const uint32_t ALU_OP_MASK        = 0x070; // bits 6:4
        const uint32_t MEM_WRITE_MASK     = 0x080; // bit 7
        const uint32_t ALU_SRC_MASK       = 0x100; // bit 8
        const uint32_t REG_WRITE_MASK     = 0x200; // bit 9
        const uint32_t JUMP_MASK          = 0x400; // bit 10

        // LSB of the ALU op code within the control unit
        // This value will be the number of times the 
        // alu opcode is shifted when crafting the control unit output signal
        const uint16_t AluOpLSB = 4;
    }
}


#endif // CONTROL_UNIT_HPP