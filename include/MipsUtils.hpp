#ifndef MIPS_UTILS_HPP
#define MIPS_UTILS_HPP

#include <cstdint>

namespace MIPSUtils
{
    uint16_t mux(uint16_t option0, uint16_t option1, bool select);
    uint32_t signExtend(uint16_t val);
}

#endif // MIPS_UTILS_HPP