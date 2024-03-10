#include "glDraw.h"

#include <iostream>
#include <GL/freeglut.h>

//#Not object oriented
#pragma warning(push)
#pragma warning(disable: 4068)
#pragma warning(disable: 6262)
#pragma warning(disable: 26451)
#define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
#pragma warning(pop)



GlDraw* GlDraw::GlDrawInstance = nullptr;



GlDraw* GlDraw::Get_Instance()
{
    if (!GlDrawInstance)
    {
        GlDrawInstance = new GlDraw();
    }
    return GlDrawInstance;
}



inline Point3D GlDraw::Get_ShiftedPosition(Point3D point)
{
    return Point3D{ point.x + (cameraShift.x * point.z), point.y + (cameraShift.y * point.z), point.z };
}

void GlDraw::Draw_Text(const std::string text, Point2D_t point)
{
    glColor3f(0.0, 1.0, 0.0);

    glRasterPos2f(point.x, point.y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
}

void GlDraw::Set_CameraShift(Point2D_t point)
{
    this->cameraShift = point;
}

void GlDraw::Draw_Dot(Point2D_t point)
{
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);

    glBegin(GL_POINTS);
    glVertex2f(point.x, point.y);
    glEnd();
}

void GlDraw::Draw_Line(Point2D_t point, Point2D_t point2)
{
    glColor3f(0.0, 1.0, 1.0);

    glBegin(GL_LINE_STRIP);

    glVertex2f(point.x, point.y);
    glVertex2f(point2.x, point2.y);

    glEnd();
}

void GlDraw::Draw_Square(Point2D_t point, Size2D size)
{
    glColor3f(0.0, 1.0, 1.0);

    glBegin(GL_LINE_STRIP);

    glVertex2f(point.x, point.y);
    glVertex2f(point.x + size.x, point.y);
    glVertex2f(point.x + size.x, point.y + size.y);
    glVertex2f(point.x, point.y + size.y);
    glVertex2f(point.x, point.y);

    glEnd();
}

void GlDraw::Draw_Array(const std::vector<float>& array, Point2D_t point)
{
    glColor3f(0.0, 1.0, 1.0);

    glBegin(GL_LINE_STRIP);

    for (size_t x = 0; x < array.size(); x++)
    {
        float _y = array[x];

        glVertex2f((x + point.x), _y + point.y);
    }

    glEnd();
}



bool GlDraw::LoadTexture(const char* filename, GLuint& textureID)
{
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

    if (image == nullptr)
    {
        std::cerr << "ERROR: Unable to load " << filename << std::endl;

        return false;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (glIsTexture(textureID) == GL_TRUE)
        return true;
    else 
        return false;
}

void GlDraw::DrawTexture(GLuint textureID, Point3D point, Size2D textureSize)
{
    point = GlDraw::Get_ShiftedPosition(point);

    glColor3f(1.0, 1.0, 1.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex3f(point.x, point.y, point.z);
    glTexCoord2f(0.0, 0.0); glVertex3f(point.x, point.y + textureSize.y, point.z);
    glTexCoord2f(1.0, 0.0); glVertex3f(point.x + textureSize.x, point.y + textureSize.y, point.z);
    glTexCoord2f(1.0, 1.0); glVertex3f(point.x + textureSize.x, point.y, point.z);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void GlDraw::DrawTexture(GLuint &textureID, const char* filename, Point3D point, Size2D textureSize)
{
    if (glIsTexture(textureID) != GL_TRUE) 
    {
        GlDraw::LoadTexture(filename, textureID);

        return;
    }
     


    point = GlDraw::Get_ShiftedPosition(point);

    glColor3f(1.0, 1.0, 1.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex3f(point.x, point.y, point.z);
    glTexCoord2f(0.0, 0.0); glVertex3f(point.x, point.y + textureSize.y, point.z);
    glTexCoord2f(1.0, 0.0); glVertex3f(point.x + textureSize.x, point.y + textureSize.y, point.z);
    glTexCoord2f(1.0, 1.0); glVertex3f(point.x + textureSize.x, point.y, point.z);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


