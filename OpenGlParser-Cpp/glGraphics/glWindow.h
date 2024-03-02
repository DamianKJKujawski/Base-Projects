#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "glScene.h"

#include <vector>
#include <GL/freeglut.h>
#include <atomic>


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

struct GlHID_s
{
    GlMouse_s mouse;
};

struct GlPoint2D_s
{
    float x;
    float y;

    GlPoint2D_s(float x = 0, float y = 0)
    {
        this->x = x;
        this->y = y;
    }
};

struct GlCamera_s
{
    float zoom;

    GlPoint2D_s position;
    GlPoint2D_s lookAt;

    GLfloat rotation;

    GlCamera_s()
    {
        zoom = 0.001f;
        rotation = 0.0f;
    }
};

struct Window_s 
{
    const char* name;
    int width;
    int height;
};



class OpenGLApp
{
private:

    static OpenGLApp* OpenGLAppInstance;

    GlScene* Current_GlScene = nullptr;

    std::atomic<bool> glutDestroyWindow_Flag = false;

    GlHID_s HID;
    GlCamera_s Camera; 

    GlPoint2D_s Mouse_lastPosition;

    void (*SpecialKeyDown_CallbackPtr)(int key, int x, int y) = nullptr;
    void (*SpecialKeyUp_CallbackPtr)(int key, int x, int y) = nullptr;



    
    OpenGLApp();



    static void SpecialKeyUpCallback(int key, int x, int y);
    void SpecialKeyUp(int key, int x, int y);
    static void SpecialKeyDownCallback(int key, int x, int y);
    void SpecialKeyDown(int key, int x, int y);
    static void MouseMotionCallback(int x, int y);
    void MouseMotion(int x, int y);
    static void ReshapeCallback(int width, int height);
    void Reshape(int width, int height);
    static void MouseWheelCallback(int wheel, int direction, int x, int y);
    void MouseWheel(int wheel, int direction, int x, int y);
    static void MouseClickCallback(int button, int state, int x, int y);
    void MouseClick(int button, int state, int x, int y);
    static void DisplayCallback();
    void Display();

public:

    //Singleton - freeglut is clear C library:
    OpenGLApp(const OpenGLApp&) = delete;
    OpenGLApp& operator=(const OpenGLApp&) = delete;

    static OpenGLApp* Get_Instance();



    ~OpenGLApp();



    void Set_SpecialKeyUpFunc(void (*SpecialKeyUpFunc)(int key, int x, int y));
    void Set_SpecialKeyDownFunc(void (*SpecialKeyDownFunc)(int key, int x, int y));
    
    void Init(std::vector<Window_s> windows, int argc, char* argv[]);

    void Set_Scene(GlScene* scene);
    void Get_CameraPointing(float mouseX, float mouseY, float& pointingX, float& pointingY);

    void Close();
};

#endif

