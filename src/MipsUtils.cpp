#include "MipsUtils.hpp"



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

