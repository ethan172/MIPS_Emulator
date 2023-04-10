#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>

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
    Memory();
    Memory(const uint16_t memSize);
    Memory(const uint16_t memSize, const T *buffer);
    ~Memory();

    // Returns an entry in @param value
    // returns true on success, false on failure
    bool getRegister(uint16_t addr, T &value) const;

    /*
    \brief adds an entry to the memory buffer
    @param [in] val value to add to the memory buffer
    @param [in] addr index where val is to be added

    @return True on success, false on failure
    */
    bool writeRegister(const T val, uint16_t addr);

    /*
    \brief Adds a collections of entries to the memory buffer
        If there is not enough space left in the buffer for all entries
        to be added then none will be added
    @param [in] entries pointer to list of entries to be added
    @param [in] numElements The number of things to be added
    @param [out] idx The index of the buffer in which the first element was added

    \return True on success, false on failure
    */
    bool writeRegisters(const T* entries, const uint16_t numElements, uint16_t startAddr);
};

#endif // MEMORY_HPP