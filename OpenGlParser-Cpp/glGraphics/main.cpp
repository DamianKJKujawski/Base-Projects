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

    _dynamicScene.Add_Dot(0);
    _dynamicScene.Add_Text2D(1);
    _dynamicScene.Add_Line(2);

    OpenGLApp* _glWindow = OpenGLApp::Get_Instance();
    std::thread _glThread(WindowThread, _glWindow, _scenePtr, argc, argv);
    


    // CMD - Text Parser:
    ParsersManager _parserManager;

    while (CMD_RESULT::EXIT != _parserManager.Execute()) 
    {}



    _glWindow->Close();

    _glThread.join();
    delete _scenePtr;

    return 0;
}