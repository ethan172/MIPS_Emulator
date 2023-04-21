#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++
CFLAGS  = -g -Wall -I

SOURCE = ./src/*
INCLUDES = ./include/
TEST_INCLUDE = ./UnitTest/include/

TARGET_FILE = MIPSEmulator
TEST_TARGET	= MIPSEmulatorTest

MIPSEmulator:
	${CC} ${CFLAGS} ${INCLUDES} -o ${TARGET_FILE} ${SOURCE} main.cpp

clean:
	rm -f ${TARGET_FILE}* *.o

.PHONY: all test clean

test:
	${CC} ${CFLAGS} ${INCLUDES} -I ${TEST_INCLUDE} -o ${TEST_TARGET} ${SOURCE} ./UnitTest/src/UnitTest.cpp

