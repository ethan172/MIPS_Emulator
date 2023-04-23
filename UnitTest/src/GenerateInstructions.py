#!/bin/python3
import json
import sys

def check_bit_lengths(opcode, rs=None, rt=None, rd=None, shamt=None, funct=None, immediate=None, addr=None):
    success = True

    if opcode > 0x3F:
        print("opcode too large")
        success = False
    
    if rs != None and rs > 0x1F:
        print("rs too large")
        success = False
    
    if rt != None and rt > 0x1F:
        print("rt too large")
        success = False
    
    if rd != None and rd > 0x1F:
        print("rd too large")
        success = False
    
    if shamt != None and shamt > 0x1F:
        print("shamt too large")
        success = False
    
    if funct != None and funct > 0x2F:
        print("funct too large")
        success = False
    
    if immediate != None and immediate > 0xFFFF:
        print("immediate too large")
        success = False
    
    if addr != None and addr > 0x3FFFFFF:
        print("address too large")
        success = False
    
    return success

def gen_RType_Instruction(opcode, rs, rt, rd, shamt, funct):
    instruction = 0x0

    if check_bit_lengths(opcode, rs=rs, rt=rt, rd=rd, shamt=shamt, funct=funct) == False:
        print("Instruction failed length checks!")
        return instruction

    instruction |= (opcode << 26)
    instruction |= (rs << 21)
    instruction |= (rt << 16)
    instruction |= (rd << 11)
    instruction |= (shamt << 6)
    instruction |= funct

    return instruction

def gen_IType_Instruction(opcode, rs, rt, immediate):
    instruction = 0x0

    if check_bit_lengths(opcode, rs=rs, rt=rt, immediate=immediate) == False:
        print("Instruction failed length checks!")
        return instruction

    instruction |= (opcode << 26)
    instruction |= (rs << 21)
    instruction |= (rt << 16)
    instruction |= immediate

    return instruction

def gen_JType_Instruction(opcode, address):
    instruction = 0x0

    if check_bit_lengths(opcode, addr=address) == False:
        print("Instruction failed length checks!")
        return instruction
    
    instruction |= (opcode << 26)
    instruction |= address

    return instruction

if __name__ == "__main__":
    
    instruction_file = "TestInstructions.bin"

    if len(sys.argv) == 2:
        instruction_file = str(sys.argv[1])
    

    with open("./UnitTest/src/InstructionBuilder.json", 'r') as builder_handle:
        builder_data = json.load(builder_handle)
    
    instructions = list()
    base = 16

    for inst in builder_data["Instructions"]:
        instruction = 0x0
        try:
            print("Processing instruction ", inst["opcode"])
            if inst["type"] == "R":
                instruction = gen_RType_Instruction(int(inst["opcode"], base),
                                                    int(inst["rs"], base),
                                                    int(inst["rt"], base),
                                                    int(inst["rd"], base),
                                                    int(inst["shamt"], base),
                                                    int(inst["funct"], base))
            elif inst["type"] == "I":
                instruction = gen_IType_Instruction(int(inst["opcode"], base),
                                                    int(inst["rs"], base),
                                                    int(inst["rt"], base),
                                                    int(inst["immediate"], base))
            elif inst["type"] == "J":
                instruction = gen_JType_Instruction(int(inst["opcode"], base),
                                                    int(inst["address"], base))
            else:
                error_string = "Invalid instruction type [" + inst["type"] + "]"
                error_string += " with opcode [" + inst["opcode"]
                print(error_string)
                continue
            
            instructions.append(instruction)

        except:
            print("Caught exception, most likely a missing field or incorrect instruction type")
        
    
    with open(instruction_file, 'w') as out_handle:
        print("Writing instructions to", instruction_file)
        for i in instructions:
            out_handle.write(f'0x{i:X}')
            out_handle.write('\n')
    
    sys.exit(0)