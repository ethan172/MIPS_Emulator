/*
To compile and run on Windows
cl /EHsc /I .\UnitTest\include\ /I .\include .\UnitTest\src\UnitTest.cpp .\src\*.cpp

.\test.exe

References
https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-alphabetically?view=msvc-170
https://learn.microsoft.com/en-us/cpp/build/reference/output-file-f-options?view=msvc-170
*/



#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_NO_POSIX_SIGNALS
#include <vector>
#include <string>

#include "catch.hpp"
#include "MipsUtils.hpp"
#include "InstructionMemory.hpp"
#include "ALU.hpp"
#include "InstructionTypes.hpp"
#include "RegisterMemory.hpp"
#include "DataMemory.hpp"


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

        CHECK(inst.fetchInstruction(size+100, registerVal) == false); // check too large of idx
        CHECK(inst.fetchInstruction(-2, registerVal) == false); // check too small of idx
    }

    SECTION("R-Type Instructions")
    {
        InstructionMemory instructionMem(2048);

        uint32_t OpCode = 0x0;
        uint32_t rs = 0x0;
        uint32_t rt = 0x0;
        uint32_t rd = 0x0;
        uint32_t shamt = 0x0;
        uint32_t funct = 0x0;
        uint32_t data;

        uint32_t instructionWord = OpCode | rs | rt | rd | shamt | funct;

        instructionMem.addInstruction(instructionWord);

        CHECK(instructionMem.fetchInstruction(0, data) == true);
        CHECK((data & RTypeInstruction::OpCodeMask) == OpCode);
        CHECK((data & RTypeInstruction::RsMask) == rs);
        CHECK((data & RTypeInstruction::RtMask) == rt);
        CHECK((data & RTypeInstruction::RdMask) == rd);
        CHECK((data & RTypeInstruction::ShamtMask) == shamt);
        CHECK((data & RTypeInstruction::FunctMask) == funct);

    }

    SECTION("Default Constructor")
    {
        InstructionMemory i;

        CHECK(i.getMemorySize() == 512); // Instruction memory by default initializes to length of 512
        CHECK(i.getMemorySizeBytes() == (512 * sizeof(uint32_t)));
    }
}

TEST_CASE("Register Memory")
{
    SECTION("Basic Test")
    {
        std::vector<uint32_t> v;
        RegisterMemory r(1000);

        for (int i = 0; i < 1000; i++)
        {
            v.push_back(i);
            r.setRegister(true, i, i);
        }

        uint32_t data;
        for (int i=0; i < 1000; i++)
        {
            r.getRegister(i, data);
            CHECK(v[i] == data);
        }

        CHECK(r.setRegister(false, 0, 0xBAD) == false);
        CHECK(r.setRegister(false, 1, 0xBADF00D) == false);
    }

    SECTION("Clear Memory")
    {
        std::vector<uint32_t> v;
        uint16_t memSize = 4096;
        RegisterMemory r(memSize);

        uint32_t data;
        for (int i = 0; i<memSize; i++)
        {
            v.push_back(i);
            r.setRegister(true, i, i);

            r.getRegister(i, data);
            CHECK(v[i] == data);
        }

        r.clearRegisters();

        // Can't guarantee memory is reallocated in the same space so can only really check the size
        CHECK(r.getMemorySize() == memSize);
    }

    SECTION("Memory Dump")
    {
        std::vector<uint32_t> v;
        uint32_t memSize = 4096;
        RegisterMemory r(memSize);
        RegisterMemory r2(memSize);
        std::string memoryFile = "RegisterMemoryDump.csv";
        std::string line;

        for (uint32_t i = 0; i<memSize; i++)
        {
            v.push_back(i);
            r.setRegister(true, i, i);
        }

        r.dumpMemory(memoryFile);

        std::ifstream in(memoryFile);
        REQUIRE(in.is_open());

        uint32_t inData, count;

        count = 0;
        std::getline(in, line); // throw out the header line
        std::getline(in, line);
        while (!in.fail())
        {
            std::istringstream(line.substr(line.find(',')+1, std::string::npos)) >> std::hex >> inData;
            CHECK(r2.setRegister(true, count, inData));
            std::getline(in, line);
            count++;
        }

        // Check the memory values read in are the same as what was printed out
        REQUIRE(r2.getMemorySize() == memSize);
        for (uint32_t i = 0; i<memSize; i++)
        {
            r2.getRegister(i, inData);
            CHECK(inData == v[i]);
        }
    }

    SECTION("Default Constructor")
    {
        RegisterMemory r;
        
        CHECK(r.getMemorySize() == 64);
        CHECK(r.getMemorySizeBytes() == (64 * sizeof(uint32_t)));
    }
}

TEST_CASE("Data Memory")
{
    SECTION("Basic Test")
    {
        uint16_t memSize = 4096;
        std::vector<uint32_t> v;
        DataMemory d(memSize);
        uint32_t data;

        for (unsigned int i = 0; i<memSize; i++)
        {
            d.setRegister(true, i, i*2);

            d.getRegister(true, i, data);
            CHECK(data == (i*2));
        }

        // Check memory write flag
        CHECK(d.setRegister(false, 0, 0xBADF00D) == false);
        d.getRegister(true, 0, data);
        CHECK(data != 0xBADF00D);
        
        // Check memory read flag
        data = 0;
        d.setRegister(true, 0, 0xA55);
        CHECK(d.getRegister(false, 0, data) == false);
        CHECK(data == 0);

        // Check bounds
        CHECK(d.setRegister(true, memSize + 1, 0xBAD) == false);
        CHECK(d.setRegister(true, -1, 0xBAD) == false);
        CHECK((d.getRegister(true, memSize + 1, data) == false && data == 0));
        CHECK((d.getRegister(true, -1, data) == false && data == 0));
    }
}

TEST_CASE("Control Unit")
{
    // TODO
}