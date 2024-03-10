#include "glWindow.h"



OpenGLApp* OpenGLApp::OpenGLApp_Instance = nullptr;



OpenGLApp* OpenGLApp::Get_Instance()
{
    if (!OpenGLApp_Instance)
    {
        OpenGLApp_Instance = new OpenGLApp();
    }
    return OpenGLApp_Instance;
}



void OpenGLApp::Init(std::vector<Window_s> windows, int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // Include alpha channel

    // Get the desktop resolution:
    int _screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int _screenHeight = GetSystemMetrics(SM_CYSCREEN);

    for (const auto& window : windows) 
    {
        int _windowWidth = window.width;
        int _windowHeight = window.height;
        int _windowX = (_screenWidth - _windowWidth) / 2;
        int _windowY = (_screenHeight - _windowHeight) / 2;

        // Set the window position:
        glutInitWindowPosition(_windowX, _windowY);
        glutInitWindowSize(_windowWidth, _windowHeight);
        int _windowPtr = glutCreateWindow(window.name);

        // Initialize OpenGL state for each window:
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Set OpenGL callbacks:
        glutDisplayFunc(DisplayCallback);
        glutReshapeFunc(ReshapeCallback);
        glutSpecialFunc(SpecialKeyDownCallback);
        glutSpecialUpFunc(SpecialKeyUpCallback);
        glutMouseFunc(MouseClickCallback);
        glutMotionFunc(MouseMotionCallback);
        glutMouseWheelFunc(MouseWheelCallback);

        //  Run:
        glutMainLoop();
    }
}



void OpenGLApp::Set_SpecialKeyUpFunc_Callback(void (*SpecialKeyUpFunc)(int key, int x, int y))
{
    glInput.Set_SpecialKeyUpFunc(SpecialKeyUpFunc);
}

void OpenGLApp::Set_SpecialKeyDownFunc_Callback(void (*SpecialKeyDownFunc)(int key, int x, int y))
{
    glInput.Set_SpecialKeyUpFunc(SpecialKeyDownFunc);
}



void OpenGLApp::SpecialKeyUpCallback(int key, int x, int y)
{
    if (OpenGLApp_Instance != nullptr)
    {
        OpenGLApp_Instance->glInput.SpecialKey_Up(key, x, y);
    }
}

void OpenGLApp::MouseMotionCallback(int x, int y)
{
    if (OpenGLApp_Instance != nullptr)
    {
        OpenGLApp_Instance->glInput.Mouse_Motion(x, y);
    }
}

void OpenGLApp::MouseWheelCallback(int wheel, int direction, int x, int y)
{
    if (OpenGLApp_Instance != nullptr)
    {
        OpenGLApp_Instance->glInput.Mouse_Wheel(direction, x, y);
    }
}

void OpenGLApp::SpecialKeyDownCallback(int key, int x, int y)
{
    if (OpenGLApp_Instance != nullptr)
    {
        OpenGLApp_Instance->glInput.SpecialKey_Down(key, x, y);
    }
}

void OpenGLApp::MouseClickCallback(int button, int state, int x, int y)
{
    if (OpenGLApp_Instance != nullptr)
    {
        OpenGLApp_Instance->glInput.Mouse_Click(button, state, x, y);
    }
}



void OpenGLApp::Set_Scene(GlScene_Base* scene)
{
    delete current_glScene_Ptr;

    current_glScene_Ptr = scene;
}



void OpenGLApp::ReshapeCallback(int width, int height)
{
    if (OpenGLApp_Instance != nullptr)
    {
        OpenGLApp_Instance->Reshape(width, height);
    }
}

void OpenGLApp::Reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glutPostRedisplay();
}



void OpenGLApp::DisplayCallback()
{
    if (OpenGLApp_Instance != nullptr)
    {
        OpenGLApp_Instance->Display();
    }
}

void OpenGLApp::Display()
{
    glutPostRedisplay();

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(camera.rotation, 0.0f, 0.0f, 1.0f);
    glScalef(camera.zoom, camera.zoom, 1.0f);
    glTranslatef(camera.position.x, camera.position.y, 0.0f);



    // Draw scene:
    if (current_glScene_Ptr)
    {
        current_glScene_Ptr->Draw(camera.position.x, camera.position.y);
    }



    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}



void OpenGLApp::Close()
{
    glutDestroyWindow(glutGetWindow());
}