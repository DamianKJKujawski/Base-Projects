#include <thread>
#include <iostream>
#include <string>
#include <windows.h>

#include "glWindow.h"
#include "glScene_Dynamic.h"

#include "parsersManager.h"




void WindowThread(OpenGLApp* glWindow, GlScene* scenePtr, int argc, char* argv[]) 
{
    glWindow->Set_Scene(scenePtr);
    glWindow->Init({ Window_s{"Dam.Ku. - OpenGL Window", 800, 600} }, argc, argv);

    delete glWindow;
}



//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
int main(int argc, char* argv[])
{
    // OpenGL Thread:
    GlScene_Dynamic _dynamicScene;
    GlScene* _scenePtr = &_dynamicScene;

    int textureWidth;
    int textureHeight;

    OpenGLApp* _glWindow = OpenGLApp::Get_Instance();
    std::thread _glThread(WindowThread, _glWindow, _scenePtr, argc, argv);
    
    GLuint _textureID1;
    GLuint _textureID2;
    const char* _filename_bck1 = "C:\\Users\\damia\\Desktop\\OpenGlParser-Cpp\\glGraphics\\x64\\Debug\\bck1.png";
    const char* _filename_bck2 = "C:\\Users\\damia\\Desktop\\OpenGlParser-Cpp\\glGraphics\\x64\\Debug\\bck2.png";

    _dynamicScene.Add_DrawTexture(0, _filename_bck2, _textureID1, Point2D{ 0, 0 }, Size2D{ 100, 100 }, -1);
    _dynamicScene.Add_DrawTexture(1, _filename_bck1, _textureID2, Point2D{ 0, 0 }, Size2D{ 100,50 }, 1);


    // CMD - Text Parser:
    ParsersManager _parserManager;

    while (CMD_RESULT::EXIT != _parserManager.Execute()) 
    {}



    _glWindow->Close();

    _glThread.join();
    delete _scenePtr;

    return 0;
}