#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>
#include <iostream>
#include <exception>

/*
Base class for a X-bit memory buffer
Utilizes the heap for the memory buffer
Is meant to be extended for specific types of memory and management
*/
template <typename T>
class Memory
{
private:
    const uint16_t MEM_SIZE;  // Size of the memory buffer
    T *m_MemoryBuffer; // Memory buffer itself

protected:
    // Constructors and copy constructors
    Memory() :
        MEM_SIZE(0)
    {
        m_MemoryBuffer = nullptr;
        initializeMemory();
    }

    Memory(const uint16_t memSize) :
        MEM_SIZE(memSize)
    {
        m_MemoryBuffer = nullptr;
        initializeMemory();
    }

    Memory(const uint16_t memSize, const T *buffer) : 
        MEM_SIZE(memSize)
    {
        m_MemoryBuffer = nullptr;
        initializeMemory();

        for (unsigned int i = 0; i < memSize; i++)
        {
            writeRegister(buffer[i]);
        }
    }

    ~Memory()
    {
        delete[] m_MemoryBuffer;
        m_MemoryBuffer = nullptr;

    }

    /*
    \brief Instantiates the private memory buffer.
            If MEM_SIZE is 0 std::length_error exception
            will be thrown.

    \return None
    */
    void initializeMemory()
    {
        if (m_MemoryBuffer != nullptr)
        {
            std::cout<<"mem buffer is not null!"<<std::endl;
            delete[] m_MemoryBuffer;
        }

        if (MEM_SIZE == 0)
        {
            throw std::length_error("Cannot allocate memory buffer of size 0");
        }

        m_MemoryBuffer = new T[MEM_SIZE];
    }

    
    /*
    \brief Returns an entry in @param value

    @param [in] addr Address to retrieve
    @param [out] value Value of the address being read

    \return True on success, false on failure
    */
    bool getRegister(uint16_t addr, T &value) const
    {
        // Check idx is in bounds of used memory
        if (addr < MEM_SIZE)
        {
            value = m_MemoryBuffer[addr];
            return true;
        }

        return false;
    }

    /*
    \brief adds an entry to the memory buffer

    @param [in] addr index where val is to be added
    @param [in] val value to add to the memory buffer

    @return True on success, false on failure
    */
    bool writeRegister(const uint16_t addr, const T val)
    {
        // Check valid address
        if (addr < MEM_SIZE)
        {
            m_MemoryBuffer[addr] = val;
            return true;
        }

        return false;
    }

    /*
    \brief Adds a collections of entries to the memory buffer
        If there is not enough space left in the buffer for all entries
        to be added then none will be added

    @param [in] entries pointer to list of entries to be added
    @param [in] numElements The number of things to be added
    @param [out] idx The index of the buffer in which the first element was added

    \return True on success, false on failure
    */
    bool writeRegisters(const T* entries, const uint16_t numElements, uint16_t startAddr)
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

    void clearMemory()
    {
        // delete then reinitialize so m_MemoryBuffer isn't null
        delete[] m_MemoryBuffer;
        initializeMemory();
    }

};

#endif // MEMORY_HPP