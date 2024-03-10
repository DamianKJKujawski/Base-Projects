#pragma once

#include "glScene_Base.h" 
#include "glDraw.h"

#include <functional>
#include <unordered_map>




class GlScene_Dynamic_Driver
{

    private:

        GlDraw* glDrawInstance = GlDraw::Get_Instance();



        std::unordered_map<size_t, std::function<bool()>> methodPointers;
        


    public:

        GlScene_Dynamic_Driver() = default;
        ~GlScene_Dynamic_Driver() = default;



        void Add_Dot(size_t idx, Point2D_t position);
        void Add_Line(size_t idx, Point2D_t point1, Point2D_t point2);
        void Add_Square(size_t idx, Point2D_t position, Size2D size);
        void Add_Array(size_t idx, const std::vector<float>& array, Point2D_t position);
        void Add_Text2D(size_t idx, const std::string text, Point2D_t position);
        
        void Add_DrawTexture(size_t idx, GLuint& textureID, Point3D position, Size2D textureSize);
        void Add_DrawTexture(size_t idx, const char* filename, GLuint& textureID, Point3D& position, Size2D textureSize);
        void Add_DrawTexture(size_t idx, const char* filename, GLuint& textureID, const Point3D& position, Size2D textureSize);
        void Add_LoadTexture(size_t idx, const char* filename, GLuint& textureID);

        void Remove_Object(size_t index);


        void Draw(float cameraPositionX, float cameraPositionY);

};