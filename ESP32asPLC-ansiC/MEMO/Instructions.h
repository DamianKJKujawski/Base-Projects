#pragma once

#include "Opcode.h"
#include "Types.h"



#pragma region STRUCTS

typedef struct
{
    uint16_t* pc;
    uint8_t* acc;
    MEM_t* ram;

} Memory_t;

typedef struct
{
    uint8_t opcode;
    void(*InstructionFunc)(Memory_t* memory, uint8_t arg);

} Instruction_t;

typedef struct
{
    Memory_t memory;
    Instruction_t* instructions;

} Instructions_t;

#pragma endregion


// Instructions Contructor (Takes pointers to: PC Register, Accumulator, RAM)
// * Instructions_t->instructions[OPCODE(enum)].InstructionFunc(&Memory_t, arg); to call instruction.
Instructions_t* Instructions(uint16_t* pc, uint8_t* acc, MEM_t* RAM);