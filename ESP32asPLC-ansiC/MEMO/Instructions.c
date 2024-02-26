#include "Instructions.h"



#pragma region PRIVATE:

    static void Instruction_SET(Memory_t* memory, uint8_t arg);
    static void Instruction_LD(Memory_t* memory, uint8_t arg);
    static void Instruction_ST(Memory_t* memory, uint8_t arg);
    static void Instruction_JMP(Memory_t* memory, uint8_t arg);
    static void Instruction_JMPA(Memory_t* memory, uint8_t arg);
    static void Instruction_ADD(Memory_t* memory, uint8_t arg);
    static void Instruction_SUB(Memory_t* memory, uint8_t arg);
    static void Instruction_AND(Memory_t* memory, uint8_t arg);
    static void Instruction_OR(Memory_t* memory, uint8_t arg);

#pragma endregion



#pragma region PUBLIC:

    Instruction_t InstructionsList[] =
    {
        {SET, Instruction_SET},
        {LD, Instruction_LD},
        {ST, Instruction_ST},

        {JMP, Instruction_JMP},
        {JMPA, Instruction_JMPA},

        {ADD, Instruction_ADD},
        {SUB, Instruction_SUB},
        {AND, Instruction_AND},
        {OR, Instruction_OR}
    };



    Instructions_t* Instructions(uint16_t* pc, uint8_t* acc, MEM_t* RAM)
    {
        Instructions_t* _instance;
        _instance = (Instructions_t*)malloc(sizeof(Instructions_t));

        if (_instance == NULL)
            return NULL;

        _instance->memory.pc = pc;
        _instance->memory.acc = acc;
        _instance->memory.ram = RAM;

        _instance->instructions = InstructionsList;

        return _instance;
    }

#pragma endregion



#pragma region METHODS:

    static void Instruction_SET(Memory_t* memory, uint8_t arg)
    {
        *(memory->acc) = arg;
    }

    static void Instruction_LD(Memory_t* memory, uint8_t arg)
    {
        *(memory->acc) = memory->ram->data[arg];
    }

    static void Instruction_ST(Memory_t* memory, uint8_t arg)
    {
        memory->ram->data[arg] = *(memory->acc);
    }

    static void Instruction_JMP(Memory_t* memory, uint8_t arg)
    {
        *(memory->pc) = arg;
    }

    static void Instruction_JMPA(Memory_t* memory, uint8_t arg)
    {
        if (memory->acc)
            *(memory->pc) = arg;
    }

    static void Instruction_ADD(Memory_t* memory, uint8_t arg)
    {
        *(memory->acc) = *(memory->acc) + memory->ram->data[arg];
    }

    static void Instruction_SUB(Memory_t* memory, uint8_t arg)
    {
        *(memory->acc) = *(memory->acc) - (memory->ram->data[arg]);
    }

    static void Instruction_AND(Memory_t* memory, uint8_t arg)
    {
        *(memory->acc) = *(memory->acc) & (memory->ram->data[arg]);
    }

    static void Instruction_OR(Memory_t* memory, uint8_t arg)
    {
        *(memory->acc) = *(memory->acc) | (memory->ram->data[arg]);
    }

#pragma endregion