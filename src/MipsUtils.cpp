#include "MipsUtils.hpp"
#include "ALU.hpp"


namespace MIPSUtils
{
    /*
    \brief Returns option 0 or 1 based on value of select

    @param [in] option0 One of two inputs to be returned
    @param [in] option1 One of two inputs to be returned
    @param [in] select When true will return option1, when false will return option0

    \return an unsigned 16bit integer
    */
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


}