#include "Memory.hpp"

template <typename T>
Memory<T>::Memory():
    MEM_SIZE(512)
{
    m_MemoryBuffer = new T[MEM_SIZE];
}

template <typename T>
Memory<T>::Memory(const uint16_t memSize):
    MEM_SIZE(memSize)
{
    m_MemoryBuffer = new T[MEM_SIZE];
}

template <typename T>
Memory<T>::Memory(const uint16_t memSize, const T *buffer):
    MEM_SIZE(memSize)
{
    m_MemoryBuffer = new T[MEM_SIZE];

    for (unsigned int i = 0; i < memSize; i++)
    {
        writeRegister(buffer[i]);
    }
}

template <typename T>
Memory<T>::~Memory()
{
    delete[] m_MemoryBuffer;
    m_MemoryBuffer = nullptr;
}

template <typename T>
bool Memory<T>::getRegister(uint16_t addr, T &value) const
{
    // Check idx is in bounds of used memory
    if (addr < MEM_SIZE)
    {
        value = m_MemoryBuffer[addr];
        return true;
    }

    return false;
}

template <typename T>
bool Memory<T>::writeRegister(const T val, uint16_t addr)
{
    // Check valid address
    if (addr < MEM_SIZE)
    {
        m_MemoryBuffer[addr] = val;
        return true;
    }

    return false;
}

template <typename T>
bool Memory<T>::writeRegisters(const T *entries, const uint16_t numElements, uint16_t startAddr)
{
    if (numElements + startAddr >= MEM_SIZE)
    {
        // Not enough space in buffer for all entries
        return false;
    }
    else if (entries == nullptr)
    {
        // No entries to add
        return false;
    }

    for (unsigned int i = 0; i < numElements; i++)
    {
        m_MemoryBuffer[startAddr+i] = *(entries + i);
    }

    return true;
}
