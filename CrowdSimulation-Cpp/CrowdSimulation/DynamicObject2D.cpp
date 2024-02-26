#include "DynamicObject2D.h"



int DynamicObject2D::x_constructor = 0;
int DynamicObject2D::y_constructor = 0;



void DynamicObject2D::Set_StartingPoint(const int x, const int y)
{
    x_constructor = x;
    y_constructor = y;
}

