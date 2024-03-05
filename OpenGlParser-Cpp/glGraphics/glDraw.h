#ifndef GLDRAW_H
#define GLDRAW_H

#include <iostream>
#include <string>
#include <vector>
#include <GL/freeglut.h>


struct Point2D 
{
    float x;
    float y;
};

typedef Point2D Size2D;

struct Point3D
{
    float x;
    float y;
    float z;
};


class GlDraw
{   

    private:

        GlDraw();
        ~GlDraw();

        static GlDraw* GlDrawInstance;

        Point2D cameraShift = Point2D{ 0,0 };



        inline Point3D Get_ShiftedPosition(Point3D point);



    public:

        static GlDraw* Get_Instance();



        void Set_CameraShift(Point2D point);

        
        bool LoadTexture(const char* filename, GLuint& textureID);
        void DrawTexture(GLuint textureID, Point3D point, Size2D textureSize);
        void DrawTexture(GLuint& textureID, const char* filename, Point3D point, Size2D textureSize);

        void Draw_Text(const std::string text, Point2D point);
        void Draw_Dot(Point2D point);
        void Draw_Line(Point2D point, Point2D point2);
        void Draw_Square(Point2D point, Size2D size);
        void Draw_Array(const std::vector<float>& array, Point2D point);
};

#endif