#include "Scene2D.h"
#include "Drawing2D.h"



Scene2D::Scene2D(int(*map)[SCENE_WIDTH][SCENE_HEIGHT])
{
    this->map = map;
}

Scene2D::~Scene2D()
{
    delete[] map;
}


void Scene2D::Set_CustomValue(int x, int y, int value)
{
    (*this->map)[x][y] += value;
}

void Scene2D::Remove_CustomValue(int x, int y, int value)
{
    (*this->map)[x][y] -= value;
}

void Scene2D::Add_DynamicObject2D(const DynamicObject2D* object2D)
{
    if (object2D != nullptr)
        (*this->map)[object2D->var_x()][object2D->var_y()] = COLOR_DYNAMIC_NUMBER;
}

void Scene2D::Remove_DynamicObject2D(const DynamicObject2D* object2D)
{
    if (object2D != nullptr)
        (*this->map)[object2D->var_x()][object2D->var_y()] = 0;
}

void Scene2D::Draw_Line(StartPoint startPoint, EndPoint endPoint, int value)
{
    Drawing2D::Draw_BresenhamLine(startPoint, endPoint, value, this->map);
}

void Scene2D::Draw_Square(StartPoint startPoint, EndPoint endPoint, int value)
{
    Drawing2D::Draw_Square(startPoint, endPoint, value, this->map);
}



void Scene2D::Print()
{
    for (int y = 0; y < SCENE_HEIGHT; y++)
    {
        for (int x = 0; x < SCENE_WIDTH; x++)
        {
            switch ((*this->map)[x][y])
            {
                case COLOR_DYNAMIC_NUMBER:
                    std::cout << COLOR_DYNAMIC_OBJECT << char(219) << char(219) << COLOR_RESET;
                    break;

                case COLOR_STATIC_NUMBER:
                    std::cout << COLOR_STATIC_OBJECT << char(219) << char(219) << COLOR_RESET;
                    break;

                case COLOR_YELLOW_NUMBER:
                    std::cout << COLOR_YELLOW << char(219) << char(219) << COLOR_RESET;
                    break;

                case COLOR_BLUE_NUMBER:
                    std::cout << COLOR_BLUE << char(219) << char(219) << COLOR_RESET;
                    break;

                default:
                    std::cout << char(219) << char(219);
                    break;
            }
        }

        std::cout << std::endl;
    }
}