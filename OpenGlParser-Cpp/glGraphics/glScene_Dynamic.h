#pragma once

#include "GlScene_Dynamic_Driver.h"



class GlScene_Dynamic : public GlScene_Base
{

private:

    GlScene_Dynamic_Driver dynamicGlScene;

    std::unordered_map<size_t, GLuint> texturePointers;



public:

    void Draw(float cameraPositionX, float cameraPositionY) override;

    void Execute_CMD(CMD_RESULT cmd, CommandData_t& outCommandData) override;

};