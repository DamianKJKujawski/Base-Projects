#include <thread>
#include <iostream>
#include <string>
#include <windows.h>

#include "glWindow.h"
#include "glScene_Dynamic.h"

#include "parsersManager.h"

#include <thread>



void WindowThread(OpenGLApp* glWindow, GlScene* scenePtr, int argc, char* argv[]) 
{
    glWindow->Set_Scene(scenePtr);
    glWindow->Init({ Window_s{"Dam.Ku. - OpenGL Window", 1200, 600} }, argc, argv);

    //animationRunning = false;

    delete glWindow;
}



//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
int main(int argc, char* argv[])
{
    // OpenGL Thread:
    GlScene_Dynamic _dynamicScene;
    GlScene* _scenePtr = &_dynamicScene;

    OpenGLApp* _glWindow = OpenGLApp::Get_Instance();
    //_glWindow->Set_SpecialKeyDownFunc(SpecialKeyDown);

    std::thread _glThread(WindowThread, _glWindow, _scenePtr, argc, argv);
    
   

    // CMD - Text Parser:
    ParsersManager _parserManager;

    std::vector<float> _vector_f(0);
    std::vector<std::string> _vector_s(0);

    CMD_RESULT _cmd_result = CMD_RESULT::EMPTY;
    while (CMD_RESULT::EXIT != _cmd_result)
    {
        _cmd_result = _parserManager.Execute(_vector_f, _vector_s);

        _dynamicScene.Add_UsingCommand(_cmd_result, _vector_f, _vector_s);
    }



    _glWindow->Close();
    _glThread.join();

    delete _scenePtr;

    return 0;
}