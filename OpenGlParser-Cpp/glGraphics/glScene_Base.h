#pragma once

#include "CMD.h"
#include "Struct.h"



class GlScene_Base
{

    public:

        virtual ~GlScene_Base() {}



        virtual void Draw(float cameraPositionX, float cameraPositionY) = 0;
        virtual void Execute_CMD(CMD_RESULT cmd, CommandData_t& outCommandData) = 0;

};