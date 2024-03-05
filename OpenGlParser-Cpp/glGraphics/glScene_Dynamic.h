#ifndef GLSCENES_H
#define GLSCENES_H

#include "glScene.h" 
#include "glDraw.h"
#include "CMD.h"
#include "iostream"
#include "string"

#include <functional>
#include <unordered_map>



class GlScene_Dynamic : public GlScene
{

    private:

        GlDraw* glDrawInstance = GlDraw::Get_Instance();

        std::unordered_map<size_t, std::function<bool()>> methodPointers;
        std::unordered_map<size_t, GLuint> texturePointers;

    public:



        GlScene_Dynamic() = default;
        ~GlScene_Dynamic() = default;



        void Add_Dot(size_t idx, Point2D position);
        void Add_Line(size_t idx, Point2D point1, Point2D point2);
        void Add_Square(size_t idx, Point2D point1, Size2D point2);
        void Add_Array(size_t idx, const std::vector<float>& array, Point2D position);
        void Add_Text2D(size_t idx, const std::string text, Point2D position);
        
        void Add_DrawTexture(size_t idx, GLuint& textureID, Point3D position, Size2D textureSize);
        void Add_DrawTexture(size_t idx, const char* filename, GLuint& textureID, Point3D& position, Size2D textureSize);
        void Add_DrawTexture(size_t idx, const char* filename, GLuint& textureID, const Point3D& position, Size2D textureSize);
        void Add_LoadTexture(size_t idx, const char* filename, GLuint& textureID);

        void Remove_Object(size_t index);


        void Add_UsingCommand(CMD_RESULT cmd, std::vector<float>& inputVector_f, std::vector<std::string>& inputVector_s)
        {
            switch (cmd)
            {
                case CMD_RESULT::GL_DRAW_POINT:
                    GlScene_Dynamic::Add_Dot((size_t)inputVector_f[0], Point2D{ inputVector_f[1], inputVector_f[2] });
                break;

                case CMD_RESULT::GL_DRAW_LINE:
                    GlScene_Dynamic::Add_Line((size_t)inputVector_f[0], Point2D{ inputVector_f[1], inputVector_f[2] }, Point2D{ inputVector_f[3], inputVector_f[4] });
                break;

                case CMD_RESULT::GL_DRAW_SQUARE:
                    GlScene_Dynamic::Add_Square((size_t)inputVector_f[0], Point2D{ inputVector_f[1], inputVector_f[2] }, Point2D{ inputVector_f[3], inputVector_f[4] });
                break;

                case CMD_RESULT::GL_DRAW_TEXT:
                {
                    std::string _inputString;

                    for (const std::string& str : inputVector_s)
                        _inputString += ' ' + str;

                    GlScene_Dynamic::Add_Text2D((size_t)inputVector_f[0], _inputString, Point2D{ inputVector_f[1], inputVector_f[2] });
                }
                break;

                case CMD_RESULT::GL_DRAW_GRAPH:
                {
                    size_t _idx = (size_t)inputVector_f[0];
                    inputVector_f.erase(inputVector_f.begin());

                    float _x = inputVector_f[0];
                    inputVector_f.erase(inputVector_f.begin());

                    float _y = inputVector_f[0];
                    inputVector_f.erase(inputVector_f.begin());

                    GlScene_Dynamic::Add_Array(_idx, inputVector_f, Point2D{ _x, _y });
                }
                break;

                case CMD_RESULT::GL_LOAD_TEXTURE:
                {
                    size_t _textureIndex = inputVector_f[0];
                    GLuint& _textureID = texturePointers[_textureIndex];

                    GlScene_Dynamic::Add_LoadTexture(inputVector_f[0], inputVector_s[0].c_str(), _textureID);
                }
                break;

                case CMD_RESULT::GL_DRAW_TEXTURE:
                {
                    if (texturePointers.find(inputVector_f[0]) != texturePointers.end()) 
                    {
                        GLuint& _textureID = texturePointers[inputVector_f[0]];

                        GlScene_Dynamic::Add_DrawTexture(inputVector_f[0], _textureID, Point3D{ inputVector_f[1], inputVector_f[2], inputVector_f[3] }, Point2D{ inputVector_f[4], inputVector_f[5] });
                    }
                }
                break;

                default:
                    break;
            }
        }


        void Draw(float cameraPositionX, float cameraPositionY) override;

};

#endif