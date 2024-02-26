#pragma once


#include "Types.h"

/* This solution doesn't work with Arduino...
* Arduino proves once again that it is a testing platform
* that does not allow for the pleasant management of large projects.
* It's just sad, because ESP32 and ESP8266 are good MCUs for projects :(
*/



#pragma region STRUCTS

typedef struct
{
    MEM_t rom;
    MEM_t ram;

    void (*Run)();

} MCU_t;

#pragma endregion



// MCU Contructor(Takes pointers to : ROM, RAM)
// * MCU_t->Run(); to run MCU process.
MCU_t* MCU(MEM_t* ROM, MEM_t* RAM);