#include "glDraw.h"

//#Not object oriented
#pragma warning(push)
#pragma warning(disable: 4068)
#pragma warning(disable: 6262)
#pragma warning(disable: 26451)
#define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
#pragma warning(pop)



GlDraw* GlDraw::GlDrawInstance = nullptr;



GlDraw::GlDraw() 
{

}

GlDraw::~GlDraw() 
{

}

GlDraw* GlDraw::Get_Instance()
{
    if (!GlDrawInstance)
    {
        GlDrawInstance = new GlDraw();
    }
    return GlDrawInstance;
}



void GlDraw::Draw_Text(const char* text, Point2D point)
{
    glColor3f(0.0, 1.0, 0.0);

    glRasterPos2f(point.x, point.y);
    for (const char* c = text; *c != '\0'; ++c)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
}

void GlDraw::Draw_Dot(Point2D point)
{
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);

    glBegin(GL_POINTS);
    glVertex2f(point.x, point.y);
    glEnd();
}

void GlDraw::Draw_Square(Point2D point, Size2D size)
{
    glColor3f(0.0, 1.0, 1.0);

    glBegin(GL_LINE_STRIP);

    glVertex3f(point.x, point.y, 0);
    glVertex3f(point.x + size.x, point.y, 0);
    glVertex3f(point.x + size.x, point.y + size.y, 0);
    glVertex3f(point.x, point.y + size.y, 0);
    glVertex3f(point.x, point.y, 0);

    glEnd();
}

void GlDraw::Draw_Array(const std::vector<double> array, float startX, float startY)
{
    glColor3f(0.0, 1.0, 1.0);

    glBegin(GL_LINE_STRIP);

    for (size_t x = 0; x < array.size(); x++)
    {
        float _y = (float)array[x];

        glVertex3f((x + startX), _y + startY, 0.0);
    }

    glEnd();
}



void GlDraw::DrawTexture(GLuint textureID)
{
    glColor3f(1.0, 1.0, 1.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 1.0, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 0.0, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void GlDraw::LoadTexture(const char* filename, int& textureWidth, int& textureHeight, GLuint& textureID)
{
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

    if (image == nullptr)
    {
        return;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    textureWidth = width;
    textureHeight = height;
}