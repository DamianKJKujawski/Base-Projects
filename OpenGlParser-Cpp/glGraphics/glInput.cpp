#include "glInput.h"



// Called by GlWindow Object / controlled by user:
void GlInput::Set_SpecialKeyUpFunc(void (*SpecialKeyUpFunc)(int key, int x, int y))
{
    SpecialKeyUp_CallbackPtr = SpecialKeyUpFunc;
}

void GlInput::Set_SpecialKeyDownFunc(void (*SpecialKeyDownFunc)(int key, int x, int y))
{
    SpecialKeyDown_CallbackPtr = SpecialKeyDownFunc;
}



void GlInput::SpecialKey_Down(const int key, const int x, const int y)
{
    if (SpecialKeyDown_CallbackPtr != nullptr)
        SpecialKeyDown_CallbackPtr(key, x, y);
}

void GlInput::SpecialKey_Up(const int key, const int x, const int y)
{
    if (SpecialKeyUp_CallbackPtr != nullptr)
        SpecialKeyUp_CallbackPtr(key, x, y);
}



void GlInput::Mouse_Motion(const int x, const int y)
{
    if (HID.mouse.right.pressed)
    {
        int _deltaX = x - (int)mouse_lastPosition.x;
        int _deltaY = y - (int)mouse_lastPosition.y;

        camera->position.x += (2 * (static_cast<float>(_deltaX) / glutGet(GLUT_WINDOW_WIDTH))) / camera->zoom;
        camera->position.y -= (2 * (static_cast<float>(_deltaY) / glutGet(GLUT_WINDOW_HEIGHT)) / camera->zoom);

        mouse_lastPosition.x = (float)x;
        mouse_lastPosition.y = (float)y;

        glutPostRedisplay();
    }
}

void GlInput::Mouse_Wheel(const int direction, const int x, const int y)
{
    if (direction > 0)
    {
        camera->zoom *= 1.1f;
    }
    else
    {
        camera->zoom /= 1.1f;
    }

    glutPostRedisplay();
}

void GlInput::Mouse_Click(const int button, const int state, const int x, const int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            HID.mouse.right.pressed = true;

            mouse_lastPosition.x = (float)x;
            mouse_lastPosition.y = (float)y;
        }
        else if (state == GLUT_UP)
        {
            HID.mouse.right.pressed = false;
        }
    }
}