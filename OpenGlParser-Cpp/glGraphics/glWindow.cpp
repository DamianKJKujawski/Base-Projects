#include "glWindow.h"



OpenGLApp* OpenGLApp::OpenGLAppInstance = nullptr;

OpenGLApp::OpenGLApp() 
{
    OpenGLAppInstance = this;
    Current_GlScene = nullptr;
}
OpenGLApp::~OpenGLApp() 
{
    delete Current_GlScene;
}

OpenGLApp* OpenGLApp::Get_Instance()
{
    if (!OpenGLAppInstance)
    {
        OpenGLAppInstance = new OpenGLApp();
    }
    return OpenGLAppInstance;
}



void OpenGLApp::Init(std::vector<Window_s> windows, int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // Updated display mode to include alpha channel

    // Get the desktop resolution
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    for (const auto& window : windows) {
        int windowWidth = window.width;
        int windowHeight = window.height;
        int windowX = (screenWidth - windowWidth) / 2;
        int windowY = (screenHeight - windowHeight) / 2;

        // Set the window position
        glutInitWindowPosition(windowX, windowY);
        glutInitWindowSize(windowWidth, windowHeight);
        int _windowPtr = glutCreateWindow(window.name);

        // Initialize OpenGL state for each window
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Set OpenGL callbacks
        glutDisplayFunc(DisplayCallback);
        glutReshapeFunc(ReshapeCallback);
        glutSpecialFunc(SpecialKeyDownCallback);
        glutSpecialUpFunc(SpecialKeyUpCallback);
        glutMouseFunc(MouseClickCallback);
        glutMotionFunc(MouseMotionCallback);
        glutMouseWheelFunc(MouseWheelCallback);

        // Additional initialization for each window can be added here

        glutMainLoop();
    }
}

void OpenGLApp::Set_Scene(GlScene* scene)
{
    delete Current_GlScene;
    Current_GlScene = scene;
}



void OpenGLApp::SpecialKeyUpCallback(int key, int x, int y)
{
    if (OpenGLAppInstance != nullptr)
    {
        OpenGLAppInstance->SpecialKeyUp(key, x, y);
    }
}

void OpenGLApp::SpecialKeyUp(int key, int x, int y)
{

}



void OpenGLApp::MouseMotionCallback(int x, int y)
{
    if (OpenGLAppInstance != nullptr)
    {
        OpenGLAppInstance->MouseMotion(x, y);
    }
}

void OpenGLApp::MouseMotion(int x, int y)
{
    if (HID.mouse.right.pressed)
    {
        int deltaX = x - Mouse_lastPosition.x;
        int deltaY = y - Mouse_lastPosition.y;

        Camera.position.x += (2 * (static_cast<float>(deltaX) / glutGet(GLUT_WINDOW_WIDTH))) / Camera.zoom;
        Camera.position.y -= (2 * (static_cast<float>(deltaY) / glutGet(GLUT_WINDOW_HEIGHT)) / Camera.zoom);

        Mouse_lastPosition.x = x;
        Mouse_lastPosition.y = y;

        glutPostRedisplay();
    }
}



void OpenGLApp::ReshapeCallback(int width, int height)
{
    if (OpenGLAppInstance != nullptr)
    {
        OpenGLAppInstance->Reshape(width, height);
    }
}

void OpenGLApp::Reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glutPostRedisplay();
}



void OpenGLApp::MouseWheelCallback(int wheel, int direction, int x, int y)
{
    if (OpenGLAppInstance != nullptr)
    {
        OpenGLAppInstance->MouseWheel(wheel, direction, x, y);
    }
}

void OpenGLApp::MouseWheel(int wheel, int direction, int x, int y)
{
    if (direction > 0)
    {
        Camera.zoom *= 1.1f;
    }
    else
    {
        Camera.zoom /= 1.1f;
    }

    glutPostRedisplay();
}



void OpenGLApp::SpecialKeyDownCallback(int key, int x, int y)
{
    if (OpenGLAppInstance != nullptr)
    {
        OpenGLAppInstance->SpecialKeyDown(key, x, y);
    }
}

void OpenGLApp::SpecialKeyDown(int key, int x, int y)
{

}



void OpenGLApp::MouseClickCallback(int button, int state, int x, int y)
{
    if (OpenGLAppInstance != nullptr)
    {
        OpenGLAppInstance->MouseClick(button, state, x, y);
    }
}

void OpenGLApp::MouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            HID.mouse.right.pressed = true;

            Mouse_lastPosition.x = x;
            Mouse_lastPosition.y = y;
        }
        else if (state == GLUT_UP)
        {
            HID.mouse.right.pressed = false;
        }
    }
}



void OpenGLApp::DisplayCallback()
{
    if (OpenGLAppInstance != nullptr)
    {
        OpenGLAppInstance->Display();
    }
}

void OpenGLApp::Close()
{
    glutDestroyWindow(glutGetWindow());
}


void OpenGLApp::Display()
{
    glutPostRedisplay();

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(Camera.rotation, 0.0f, 0.0f, 1.0f);
    glScalef(Camera.zoom, Camera.zoom, 1.0f);
    glTranslatef(Camera.position.x, Camera.position.y, 0.0f);


    // Here we draw scene:
    if (Current_GlScene)  {
        Current_GlScene->Draw();
    }


    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void OpenGLApp::Get_CameraPointing(float mouseX, float mouseY, float& pointingX, float& pointingY)
{
    int _width = glutGet(GLUT_WINDOW_WIDTH);
    int _height = glutGet(GLUT_WINDOW_HEIGHT);

    float normalizedX = (2.0f * mouseX) / _width - 1.0f;
    float normalizedY = 1.0f - (2.0f * mouseY) / _height;

    float invZoomFactor = Camera.zoom;
    float invOffsetX = -Camera.position.x;
    float invOffsetY = -Camera.position.y;
    float invViewRotation = -Camera.rotation;

    float rotatedX = normalizedX * cos(invViewRotation * 3.14159265f / 180.0f) - normalizedY * sin(invViewRotation * 3.14159265f / 180.0f);
    float rotatedY = normalizedX * sin(invViewRotation * 3.14159265f / 180.0f) + normalizedY * cos(invViewRotation * 3.14159265f / 180.0f);

    pointingX = rotatedX / invZoomFactor + invOffsetX;
    pointingY = rotatedY / invZoomFactor + invOffsetY;
}

