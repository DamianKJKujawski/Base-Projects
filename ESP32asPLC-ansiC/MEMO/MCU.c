#include "MCU.h"
#include "Instructions.h"



#pragma region PRIVATE:

    static MCU_t* instance = NULL;

    static Instructions_t* instructions;

    //uC Registers:
    static uint8_t acc = 0;
    static uint16_t pc = 0;

    static void Run();

#pragma endregion



#pragma region PUBLIC:

    MCU_t * MCU(MEM_t* ROM, MEM_t* RAM)
    {
        if (!instance)
        {
            instance = (MCU_t*)malloc(sizeof(MCU_t));

            if (instance)
            {
                instance->rom.data = ROM->data;
                instance->rom.size = ROM->size;

                instance->ram.data = RAM->data;
                instance->ram.size = RAM->size;

                instance->Run = Run; // Set the execute function pointer

                instructions = Instructions(&pc, &acc, RAM);

                if (!instructions)
                {
                    free(instance);

                    instance = NULL;
                }
            }
        }

        return instance;
    }

#pragma endregion



#pragma region METHODS:

    static void Run()
    {
        uint8_t* _romProgram = instance->rom.data;
        size_t _romSize = instance->rom.size;

        uint8_t* _ramData = instance->ram.data;
        size_t _ramSize = instance->ram.size;

        for (pc = 0; pc < _romSize; pc += 2)
        {
            uint8_t _oppcode = _romProgram[pc] & 0x0F;
            uint16_t _arg = ((_romProgram[pc] & 0xF0) << 4) | _romProgram[pc + 1];

            instructions->instructions[_oppcode].InstructionFunc(&instructions->memory, _arg);
        }
    }

#pragma endregion