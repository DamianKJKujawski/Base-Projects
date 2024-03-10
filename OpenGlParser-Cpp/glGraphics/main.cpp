#include <thread>
#include <iostream>
#include <string>
#include <windows.h>

#include "glWindow.h"
#include "glScene_Dynamic.h"

#include "parser.h"

#include <thread>

#include "Struct.h"



void Window_Thread(OpenGLApp* glWindow, GlScene_Base* scenePtr, int argc, char* argv[])
{
    glWindow->Set_Scene(scenePtr);
    glWindow->Init({ Window_s{"Dam.Ku. - OpenGL Window", 1200, 600} }, argc, argv);
}



//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
int main(int argc, char* argv[])
{
    // OpenGL Thread:
    GlScene_Dynamic _dynamicGlScene;
    GlScene_Base* _scenePtr = &_dynamicGlScene;

    OpenGLApp* _glWindow = OpenGLApp::Get_Instance();
    // _glWindow->Set_SpecialKeyDownFunc_Callback(SpecialKeyDown);

    std::thread _glWindow_Thread(Window_Thread, _glWindow, _scenePtr, argc, argv);
    
   

    // CMD - Text Parser:
    Parser _parser;
    CommandData_t _commandData;

    CMD_RESULT _cmd_result = CMD_RESULT::EMPTY;
    while (CMD_RESULT::EXIT != _cmd_result)
    {
        // 1. Interprete input data:
        CMD_RESULT _cmd_result = _parser.Parse_CMD(_commandData);

        // 2. Interprete result for PARSERS (CMD/MATH):
        _parser.Execute_CMD(_cmd_result, _commandData);

        // 3. Interprete result for GL_WINDOW:
        _dynamicGlScene.Execute_CMD(_cmd_result, _commandData);

        // 4. Print result:
        _parser.DisplayResult(_commandData);
    }



    _glWindow->Close();
    _glWindow_Thread.join();

    delete _scenePtr;
    delete _glWindow;

    return 0;
}