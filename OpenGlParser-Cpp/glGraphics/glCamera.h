#pragma once

#include "Struct.h"
#include <GL/freeglut.h>



class GlCamera
{

    GlCamera_t* camera;



public:

    GlCamera(GlCamera_t* glCameraPtr)
    {
        camera = glCameraPtr;
    }

    ~GlCamera()
    {
        delete camera;
    }



	void Get_CameraPointing(const float mouseX, const float mouseY, float& pointingX, float& pointingY);

};
