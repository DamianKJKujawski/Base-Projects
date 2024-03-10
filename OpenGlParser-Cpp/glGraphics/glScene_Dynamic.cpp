#pragma once

#include "GlScene_Dynamic.h"



void GlScene_Dynamic::Draw(float cameraPositionX, float cameraPositionY)
{
    dynamicGlScene.Draw(cameraPositionX, cameraPositionY);
}

void GlScene_Dynamic::Execute_CMD(CMD_RESULT cmd, CommandData_t& outCommandData)
{
    switch (cmd)
    {

        case CMD_RESULT::GL_DRAW_POINT:
            dynamicGlScene.Add_Dot((size_t)outCommandData.vector_float[0], Point2D_t{ outCommandData.vector_float[1], outCommandData.vector_float[2] });
            break;

        case CMD_RESULT::GL_DRAW_LINE:
            dynamicGlScene.Add_Line((size_t)outCommandData.vector_float[0], Point2D_t{ outCommandData.vector_float[1], outCommandData.vector_float[2] }, Point2D_t{ outCommandData.vector_float[3], outCommandData.vector_float[4] });
            break;

        case CMD_RESULT::GL_DRAW_SQUARE:
            dynamicGlScene.Add_Square((size_t)outCommandData.vector_float[0], Point2D_t{ outCommandData.vector_float[1], outCommandData.vector_float[2] }, Point2D_t{ outCommandData.vector_float[3], outCommandData.vector_float[4] });
            break;

        case CMD_RESULT::GL_DRAW_TEXT:
        {
            std::string _inputString;

            for (const std::string& str : outCommandData.vector_string)
                _inputString += ' ' + str;

            dynamicGlScene.Add_Text2D((size_t)outCommandData.vector_float[0], _inputString, Point2D_t{ outCommandData.vector_float[1], outCommandData.vector_float[2] });
        }
        break;

        case CMD_RESULT::GL_DRAW_GRAPH:
        {
            size_t _idx = (size_t)outCommandData.vector_float[0];
            outCommandData.vector_float.erase(outCommandData.vector_float.begin());

            float _x = outCommandData.vector_float[0];
            outCommandData.vector_float.erase(outCommandData.vector_float.begin());

            float _y = outCommandData.vector_float[0];
            outCommandData.vector_float.erase(outCommandData.vector_float.begin());

            dynamicGlScene.Add_Array(_idx, outCommandData.vector_float, Point2D_t{ _x, _y });
        }
        break;

        case CMD_RESULT::GL_LOAD_TEXTURE:
        {
            size_t _textureIndex = (size_t)outCommandData.vector_float[0];
            GLuint& _textureID = texturePointers[_textureIndex];

            dynamicGlScene.Add_LoadTexture((size_t)outCommandData.vector_float[0], outCommandData.vector_string[0].c_str(), _textureID);
        }
        break;

        case CMD_RESULT::GL_DRAW_TEXTURE:
        {
            if (texturePointers.find((size_t)outCommandData.vector_float[0]) != texturePointers.end())
            {
                GLuint& _textureID = texturePointers[(int)outCommandData.vector_float[0]];

                dynamicGlScene.Add_DrawTexture((size_t)outCommandData.vector_float[0], _textureID, Point3D{ outCommandData.vector_float[1], outCommandData.vector_float[2], outCommandData.vector_float[3] }, Point2D_t{ outCommandData.vector_float[4], outCommandData.vector_float[5] });
            }
        }
        break;

        case CMD_RESULT::CMD_REMOVE:
        {
            size_t _idx = (size_t)outCommandData.vector_float[0];

            dynamicGlScene.Remove_Object(_idx);
        }
        break;

        default:
        break;

    }
}