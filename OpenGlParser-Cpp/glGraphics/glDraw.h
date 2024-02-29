#ifndef GLDRAW_H
#define GLDRAW_H

#include <vector>
#include <GL/freeglut.h>


struct Point2D 
{
    float x;
    float y;
};

typedef Point2D Size2D;



class GlDraw
{   

    private:

        GlDraw();
        ~GlDraw();

        static GlDraw* GlDrawInstance;



    public:

        static GlDraw* Get_Instance();

        void LoadTexture(const char* filename, int& textureWidth, int& textureHeight, GLuint& textureID);
        void DrawTexture(GLuint textureID);

        void Draw_Text(const char* text, Point2D point);
        void Draw_Dot(Point2D point);
        void Draw_Square(Point2D point, Size2D size);
        void Draw_Array(const std::vector<double> array, float startX, float startY);
};

#endif