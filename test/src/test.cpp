/*
To compile and run
cl /EHsc /I .\test\include\ /I .\include .\test\src\test.cpp .\src\*.cpp

.\test.exe

References
https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-alphabetically?view=msvc-170
https://learn.microsoft.com/en-us/cpp/build/reference/output-file-f-options?view=msvc-170
*/



#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Mux.hpp"
#include "MipsUtils.hpp"


TEST_CASE("Mux")
{
    Mux m;

    uint16_t input0 = 16;
    uint16_t input1 = 10;
    bool select = 0;

    m.setOption0(input0);
    m.setOption1(input1);

    CHECK(m.getOption0() == input0);
    CHECK(m.getOption1() == input1);

    CHECK(m.evaluate(select) == input0);
    
    m.setSelect(select);

    CHECK(m.evaluate() == input0);
}

TEST_CASE("Utils")
{
    uint16_t val = 0x5;

    CHECK(signExtend(val) == 0x00000005);

    val = 0x8005;
    CHECK(signExtend(val) == 0xFFFF8005);
}