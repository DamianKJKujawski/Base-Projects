#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "glScene_Base.h"
#include "glInput.h"
#include "glCamera.h"



class OpenGLApp
{

private:

    static OpenGLApp* OpenGLApp_Instance;

    GlScene_Base* current_glScene_Ptr = nullptr;

    GlCamera_t camera;

    GlCamera camera_Controller = GlCamera(&camera);
    GlInput glInput = GlInput(&camera);

    

    OpenGLApp()
    {
        OpenGLApp_Instance = this;
    }



    static void ReshapeCallback(int width, int height);
    void Reshape(int width, int height);
    
    static void DisplayCallback();
    void Display();

    static void SpecialKeyUpCallback(int key, int x, int y);
    static void SpecialKeyDownCallback(int key, int x, int y);
    static void MouseMotionCallback(int x, int y);
    static void MouseWheelCallback(int wheel, int direction, int x, int y);
    static void MouseClickCallback(int button, int state, int x, int y);



public:

    // Singleton - freeglut is clear C library:
    // * Preventing opening another window *
    OpenGLApp(const OpenGLApp&) = delete;
    OpenGLApp& operator=(const OpenGLApp&) = delete;

    static OpenGLApp* Get_Instance();



    ~OpenGLApp()
    {
        delete current_glScene_Ptr;
    }



    void Init(std::vector<Window_s> windows, int argc, char* argv[]);

    void Set_Scene(GlScene_Base* scene);

    void Set_SpecialKeyUpFunc_Callback(void (*SpecialKeyUpFunc)(int key, int x, int y));
    void Set_SpecialKeyDownFunc_Callback(void (*SpecialKeyDownFunc)(int key, int x, int y));

    void Close();

};

#endif

