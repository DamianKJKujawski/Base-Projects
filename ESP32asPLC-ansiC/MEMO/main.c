#include "MCU.h"
#include "Opcode.h"
#include "Project.h"

#include <stdio.h>



int main()
{
    unsigned char _romProgram[] =
    {
        SET, 3,
        ST, 0,
        ADD, 0,
        ST, 1
    };

    unsigned char _ramData[256] = { 0 };



    // According to PLC workflow:
    // While(true)
    // {
    // Scan_INPUT() || For Example: INPUT -> _ramData[254] 
    MCU_t* _mcuSimulation = MCU
    (
        &(MEM_t) { (unsigned char*)_romProgram, sizeof(_romProgram) },
        &(MEM_t) { _ramData, sizeof(_ramData) }
    );

    _mcuSimulation->Run();
    // Set_OUTPUT() || For Example: _ramData[255] -> OUTPUT  
    // }

    free(_mcuSimulation);



    //Result:
    printf("RAM map:\n");
    for (int i = 0; i < sizeof(_ramData); i++)
    {
        printf("%d ", _ramData[i]); // Print the current element followed by a space
    }



    (void)getchar();
}

