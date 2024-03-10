#ifndef GLDRAW_H
#define GLDRAW_H

#include "Struct.h"



class GlDraw
{   

    private:

        GlDraw() {};
        ~GlDraw() {};



        static GlDraw* GlDrawInstance;

        Point2D_t cameraShift = Point2D_t{ 0,0 };



        inline Point3D Get_ShiftedPosition(Point3D point);



    public:

        static GlDraw* Get_Instance();



        void Set_CameraShift(Point2D_t point);

        bool LoadTexture(const char* filename, GLuint& textureID);
        void DrawTexture(GLuint textureID, Point3D point, Size2D textureSize);
        void DrawTexture(GLuint& textureID, const char* filename, Point3D point, Size2D textureSize);

        void Draw_Text(const std::string text, Point2D_t point);
        void Draw_Dot(Point2D_t point);
        void Draw_Line(Point2D_t point, Point2D_t point2);
        void Draw_Square(Point2D_t point, Size2D size);
        void Draw_Array(const std::vector<float>& array, Point2D_t point);

};

#endif