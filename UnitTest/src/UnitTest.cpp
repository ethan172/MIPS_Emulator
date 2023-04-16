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
#include "ALU.hpp"


TEST_CASE("Utils")
{
    uint16_t val = 0x5;

    CHECK(MIPSUtils::signExtend(val) == 0x00000005);

    val = 0x8005;
    CHECK(MIPSUtils::signExtend(val) == 0xFFFF8005);
}

TEST_CASE("ALU")
{
    SECTION("Add")
    {
        ALU alu;

        int32_t lhs, rhs, result;
        bool zero, overflow, carry;

        lhs = 100;
        rhs = 5;

        alu.setOpCode(0);
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        CHECK(result == 105);
        CHECK(zero == false);
        CHECK(overflow == false);
        CHECK(carry == false);

        lhs = -100;
        rhs = -5;
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        CHECK(result == -105);
        CHECK(zero == false);
        CHECK(overflow == false);
        CHECK(carry == false);

        lhs = 2147483647; // max value of int32
        rhs = 1;
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        CHECK(result == -2147483648);
        CHECK(zero == false);
        CHECK(overflow == true);
        CHECK(carry == true);

        lhs = -1;
        rhs = -2147483648; // min value of int32
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        CHECK(result == 2147483647);
        CHECK(zero == false);
        CHECK(overflow == true);
        CHECK(carry == true);

        lhs = 0;
        rhs = 0;
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        CHECK(result == 0);
        CHECK(zero == true);
        CHECK(overflow == false);
        CHECK(carry == false);
    }

    SECTION("Sub")
    {
        ALU alu;
        uint32_t lhs, rhs, result;
        bool zero, overflow, carry;

        alu.setOpCode(1);

        lhs = 500;
        rhs = 100;
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        CHECK(result == 400);
        CHECK(zero == false);
        CHECK(overflow == false);
        CHECK(carry == false);

        lhs = 2147483647; // max value of int32
        rhs = lhs;
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        CHECK(result == 0);
        CHECK(zero == true);
        CHECK(overflow == false);
        CHECK(carry == false);

        lhs = -2147483648; // min value
        rhs = 1;
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        /*
        1111 1111 1111 1111 1111 1111 1111 1111

        0000 0000 0000 0000 0000 0000 0000 0001
        
        1000 0000 0000 0000 0000 0000 0000 0000 
        1111 1111 1111 1111 1111 1111 1111 1111 // -1 
        0111 1111 1111 1111 1111 1111 1111 1111 + overflow & carry
        
        */
        CHECK(result == 0x7FFFFFFF);
        CHECK(zero == false);
        CHECK(overflow == true);
        CHECK(carry == true);

    }

    SECTION("And")
    {
        ALU alu;

        uint32_t lhs, rhs, result;
        bool zero, overflow, carry;

        alu.setOpCode(3);

        lhs = 0x0000000F;
        rhs = 0xFFFFFFFF;
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        CHECK(result == 0xF);
        CHECK(zero == false);
        CHECK(overflow == false);
        CHECK(carry == false);

        lhs = 0xBADF00D;
        rhs = 0x0;
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        CHECK(result == 0x0);
        CHECK(zero == true);
        CHECK(overflow == false);
        CHECK(carry == false);

        lhs = 0xF0000001;
        rhs = 0x00000001;
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        CHECK(result == 0x1);
        CHECK(zero == false);
        CHECK(overflow == false);
        CHECK(carry == false);
    }

    SECTION("Or")
    {
        ALU alu;
        uint32_t lhs, rhs, result;
        bool zero, overflow, carry;

        alu.setOpCode(2);

        lhs = 0x0;
        rhs = 0xFFFFFFFF;
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        CHECK(result == 0xFFFFFFFF);
        CHECK(zero == false);
        CHECK(overflow == false);
        CHECK(carry == false);

        lhs = 0xBAD0000;
        rhs = 0x000F00D;
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        CHECK(result == 0xBADF00D);
        CHECK(zero == false);
        CHECK(overflow == false);
        CHECK(carry == false);

        lhs = 0;
        rhs = 0;
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        CHECK(result == 0);
        CHECK(zero == true);
        CHECK(overflow == false);
        CHECK(carry == false);
    }

    SECTION("Slt")
    {
        ALU alu;
        int32_t lhs, rhs, result;
        bool zero, overflow, carry;

        alu.setOpCode(4);

        lhs = -2147483648;
        rhs = 5;
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        CHECK(result == 1);
        CHECK(zero == false);
        CHECK(overflow == false);
        CHECK(carry == false);

        lhs = 2147483647;
        rhs = 0;
        result = alu.evaluate(lhs, rhs, zero, overflow, carry);

        CHECK(result == 0);
        CHECK(zero == true);
        CHECK(overflow == false);
        CHECK(carry == false);
    }
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
            CHECK(inst.fetchInstruction(i, instOut));

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
            CHECK(inst.fetchInstruction(i, registerVal));
            CHECK(registerVal == entries[i]);
        }

        CHECK(inst.fetchInstruction(size+100, registerVal) == false);
    }
}
