#pragma once



enum OPCODE
{
    SET,
    LD, //0x1X <- X - Most significant bits of address
    ST, //0x2X <- X - Most significant bits of address

    JMP, //If Accu != 0
    JMPA, //If Accu != 0

    ADD,
    SUB,
    AND,
    OR,

    NOP
}; 
