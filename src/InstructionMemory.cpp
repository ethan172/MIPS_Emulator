#include "InstructionMemory"

InstructionMemory::InstructionMemory() :
    m_BufferSize(100)
{
    m_MemoryBuffer = new uint32_t(m_BufferSize);
}