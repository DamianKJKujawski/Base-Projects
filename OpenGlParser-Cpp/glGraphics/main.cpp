#include <thread>
#include <iostream>
#include <string>
#include <windows.h>

#include "glWindow.h"
#include "glScene_Dynamic.h"

#include "parsersManager.h"

#include <thread>



std::atomic<bool> animationRunning(true);



void WindowThread(OpenGLApp* glWindow, GlScene* scenePtr, int argc, char* argv[]) 
{
    glWindow->Set_Scene(scenePtr);
    glWindow->Init({ Window_s{"Dam.Ku. - OpenGL Window", 1200, 600} }, argc, argv);

    animationRunning = false;

    delete glWindow;
}

void AnimationThread(GlScene_Dynamic* dynamicScene)
{
    while (animationRunning)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        dynamicScene->animationStep += 0.2;

        if (dynamicScene->animationStep > 1.3)
            dynamicScene->animationStep = 0;
    }
}

Point3D _pp = { -140, -70, 0.3 };

void SpecialKeyDown(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT)
        _pp.x--;

    if (key == GLUT_KEY_RIGHT)
        _pp.x++;
}



//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
int main(int argc, char* argv[])
{
    // OpenGL Thread:
    GlScene_Dynamic _dynamicScene;
    GlScene* _scenePtr = &_dynamicScene;

    OpenGLApp* _glWindow = OpenGLApp::Get_Instance();
    _glWindow->Set_SpecialKeyDownFunc(SpecialKeyDown);

    std::thread _glThread(WindowThread, _glWindow, _scenePtr, argc, argv);
    
    

    // DynamicScene Thread:
    GLuint _textureID[3];

    const char* _filename_bck1 = "C:\\Users\\damia\\Desktop\\OpenGlParser-Cpp\\glGraphics\\x64\\Debug\\bck1.png";
    const char* _filename_bck2 = "C:\\Users\\damia\\Desktop\\OpenGlParser-Cpp\\glGraphics\\x64\\Debug\\bck3.png";
    const char* _filename_bck3 = "C:\\Users\\damia\\Desktop\\OpenGlParser-Cpp\\glGraphics\\x64\\Debug\\bck2.png";



    // Background:
    _dynamicScene.Add_DrawTexture(0, _filename_bck3, _textureID[0], Point3D{ -120, -50, 0.0 }, Size2D{ 180, 100 },  0);
    _dynamicScene.Add_DrawTexture(1, _filename_bck2, _textureID[1], Point3D{ -120, -50, 0.0 }, Size2D{ 180, 100 },  1);

    _dynamicScene.Add_Text2D(2, "Version 1.0.0", Point2D{ -60,-20 });
    // Foreground:
    _dynamicScene.Add_DrawTexture(3, _filename_bck1, _textureID[2], _pp, Size2D{ 200, 120 }, -1);

    
    
    std::thread _glThread_Animation(AnimationThread, &_dynamicScene);



    // CMD - Text Parser:
    ParsersManager _parserManager;

    while (CMD_RESULT::EXIT != _parserManager.Execute()) 
    {}



    _glWindow->Close();

    _glThread.join();
    _glThread_Animation.join();

    delete _scenePtr;

    return 0;
}