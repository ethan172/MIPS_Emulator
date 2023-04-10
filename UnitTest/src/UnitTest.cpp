/*
To compile and run
cl /EHsc /I .\test\include\ /I .\include .\test\src\test.cpp .\src\*.cpp

.\test.exe

References
https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-alphabetically?view=msvc-170
https://learn.microsoft.com/en-us/cpp/build/reference/output-file-f-options?view=msvc-170
*/



#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_NO_POSIX_SIGNALS
#include <vector>

#include "catch.hpp"
#include "MipsUtils.hpp"
#include "InstructionMemory.hpp"


TEST_CASE("Utils")
{
    uint16_t val = 0x5;

    CHECK(signExtend(val) == 0x00000005);

    val = 0x8005;
    CHECK(signExtend(val) == 0xFFFF8005);
}

TEST_CASE("InstructionMemory")
{
    SECTION("Basic Entry Adding")
    {
        uint16_t memSize = 2048;
        std::vector<uint32_t> v;
        InstructionMemory inst(memSize);

        // use the std::vector as the 'gold file'

        for (unsigned int i=0; i<memSize; i++)
        {
            v.push_back(i);
        }

        for (unsigned int i=0; i<v.size(); i++)
        {
            inst.addInstruction(i);
        }

        uint32_t instOut;
        for (unsigned int i=0; i<v.size(); i++)
        {
            CHECK(inst.getInstruction(i, instOut));

            CHECK(instOut == v[i]);
        }
    }

    SECTION("Multiple Entry Adding")
    {
        uint16_t size = 1000;
        uint32_t entries[size];
        InstructionMemory inst(size);

        for (unsigned int i = 0; i<size; i++)
        {
            entries[i] = 0xA000 + i;
        }

        for (unsigned int i = 0; i<size; i++)
        {
            CHECK(inst.addInstruction(entries[i]));
        }

        // not enough memory to add another instruction
        CHECK(inst.addInstruction(0xBAD) == false);

        uint32_t registerVal;
        for (unsigned int i = 0; i<size; i++)
        {
            // Check getting value returns success and value matches expected
            CHECK(inst.getInstruction(i, registerVal));
            CHECK(registerVal == entries[i]);
        }

        CHECK(inst.getInstruction(size+100, registerVal) == false);
    }
}