#pragma once

#include <vector>
#include <GL/freeglut.h>

#include "Struct.h"


class GlInput
{

private:

	GlHID_s HID;

	Point2D_t mouse_lastPosition;
	GlCamera_t* camera;


	void (*SpecialKeyDown_CallbackPtr)(int key, int x, int y) = nullptr;
	void (*SpecialKeyUp_CallbackPtr)(int key, int x, int y) = nullptr;



public:

	GlInput(GlCamera_t* cameraPtr)
	{
		this->camera = cameraPtr;
	}

	~GlInput()
	{
		if (camera != nullptr)
			delete camera;
	}



	void Set_SpecialKeyUpFunc(void (*SpecialKeyUpFunc)(int key, int x, int y));
	void Set_SpecialKeyDownFunc(void (*SpecialKeyDownFunc)(int key, int x, int y));

	void SpecialKey_Down(const int key, const int x, const int y);
	void SpecialKey_Up(const int key, const int x, const int y);
	

	void Mouse_Motion(const int x, const int y);
	void Mouse_Wheel(const int direction, const int x, const int y);
	void Mouse_Click(const int button, const int state, const int x, const int y);

};