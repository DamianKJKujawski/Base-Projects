#include "glCamera.h"



void GlCamera::Get_CameraPointing(const float mouseX, const float mouseY, float& pointingX, float& pointingY)
{
    int _width = glutGet(GLUT_WINDOW_WIDTH);
    int _height = glutGet(GLUT_WINDOW_HEIGHT);

    float _normalizedX = (2.0f * mouseX) / _width - 1.0f;
    float _normalizedY = 1.0f - (2.0f * mouseY) / _height;
    float _invOffsetX = -camera->position.x;
    float _invOffsetY = -camera->position.y;
    float _invViewRotation = -camera->rotation;

    float _rotatedX = _normalizedX * cos(_invViewRotation * 3.14159265f / 180.0f) - _normalizedY * sin(_invViewRotation * 3.14159265f / 180.0f);
    float _rotatedY = _normalizedX * sin(_invViewRotation * 3.14159265f / 180.0f) + _normalizedY * cos(_invViewRotation * 3.14159265f / 180.0f);

    pointingX = _rotatedX / camera->zoom + _invOffsetX;
    pointingY = _rotatedY / camera->zoom + _invOffsetY;
}
