#ifndef GLSCENES_H
#define GLSCENES_H

#include "glScene.h" 
#include "glDraw.h"

#include <functional>
#include <unordered_map>



class GlScene_Dynamic : public GlScene
{

    private:

        GlDraw* glDrawInstance = GlDraw::Get_Instance();

        std::unordered_map<size_t, std::function<void()>> methodPointers;



    public:

        GlScene_Dynamic() = default;
        ~GlScene_Dynamic() = default;



        void Add_Dot(size_t idx, Point2D position);
        void Add_Line(size_t idx, Point2D point1, Point2D point2);
        void Add_Square(size_t idx, Point2D point1, Size2D point2);
        void Add_Text2D(size_t idx, const char* text, Point2D position);
        void Add_DrawTexture(size_t idx, const char* filename, GLuint& textureID, Point2D position, Size2D textureSize, GLfloat z);

        void Remove_Object(size_t index);

        void Draw() override; 

};

#endif