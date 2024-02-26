#include <math.h>
#include <algorithm>

#include "Drawing2D.h"



#pragma region PUBLIC:

    // Bresenham algorithm:
    void Drawing2D::Draw_BresenhamLine(StartPoint startPoint, EndPoint endPoint, int value, int(*map)[SCENE_WIDTH][SCENE_HEIGHT])
    {
        int _delta_x = abs(endPoint.x - startPoint.x);
        int _delta_y = abs(endPoint.y - startPoint.y);

        int _vector_x = startPoint.x < endPoint.x ? 1 : -1;
        int _vector_y = startPoint.y < endPoint.y ? 1 : -1;



        int _error = _delta_x - _delta_y;

        while (startPoint.x != endPoint.x || startPoint.y != endPoint.y)
        {
            (*map)[startPoint.x][startPoint.y] = value;

            int _error_x2 = 2 * _error;

            if (_error_x2 > -_delta_y)
            {
                _error -= _delta_y;
                startPoint.x += _vector_x;
            }

            if (_error_x2 < _delta_x)
            {
                _error += _delta_x;
                startPoint.y += _vector_y;
            }
        }

        (*map)[startPoint.x][startPoint.y] = value; // Ensure the end point is also drawn
    }

    void Drawing2D::Draw_Square(StartPoint startPoint, EndPoint endPoint, int value, int(*map)[SCENE_WIDTH][SCENE_HEIGHT])
    {
        int _start_x = std::min(startPoint.x, endPoint.x);
        int _end_x = std::max(startPoint.x, endPoint.x);

        int _start_y = std::min(startPoint.y, endPoint.y);
        int _end_y = std::max(startPoint.y, endPoint.y);



        for (int x = _start_x; x < _end_x; ++x) 
        {
            for (int y = _start_y; y < _end_y; ++y) 
            {
                (*map)[x][y] = value;
            }
        }
    }

#pragma endregion