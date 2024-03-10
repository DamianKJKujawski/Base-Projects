#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <GL/freeglut.h>



// Between-classes communication:
typedef struct CommandData_t
{
	std::string result;

	std::vector<float> vector_float;
	std::vector<std::string> vector_string;


	CommandData_t() : result(""), vector_float(0), vector_string(0) {}

} CommandData_t;



// IO:
struct GlButton
{
    bool pressed;

    GlButton()
    {
        pressed = false;
    }
};

struct GlMouse_s
{
    GlButton right;
};

typedef struct GlHID_s
{
    GlMouse_s mouse;

} GlHID_s;



// GFX:
struct Point3D
{
    float x;
    float y;
    float z;
};

typedef struct Point2D_t
{
    float x;
    float y;


    Point2D_t(float x = 0, float y = 0)
    {
        this->x = x;
        this->y = y;
    }

} Point2D_t;

typedef Point2D_t Size2D;



// Camera:
typedef struct GlCamera_t
{
    GLfloat zoom;
    GLfloat rotation;

    Point2D_t position;
    Point2D_t lookAt;


    GlCamera_t() : zoom(0.001f), rotation(0.0f) {}

} GlCamera_t;



// Window:
typedef struct Window_s
{
    const char* name;
    int width;
    int height;

} Window_s;