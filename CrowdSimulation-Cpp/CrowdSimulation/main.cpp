#include <chrono>

#include "Scene2D.h"
#include "DynamicObject2D_Fast.h"
#include "Debug.h"



void Draw_Scene(Scene2D& _scene2D);



int main() 
{
    // Map array:
    int _map[SCENE_WIDTH][SCENE_HEIGHT] = { 0 };

    // Create dynamic objects:
    DynamicObject2D::Set_StartingPoint(38, 38);
    DynamicObject2D* _obj_Base = new DynamicObject2D_Fast[DYNAMIC_OBJECT_CNT];

    DynamicObject2D_Fast* _obj = static_cast<DynamicObject2D_Fast*>(_obj_Base);



    // Scene:
    Scene2D _scene2D(&_map);
    Draw_Scene(_scene2D);

    // Set movement target:
    Object2D _target(10, 10);



    while (true)
    {   
    #ifdef DEBUG_ENABLED
        std::chrono::steady_clock::time_point _startTime;
        std::chrono::duration<double> _duration = std::chrono::duration<double>::zero();
    #endif

        for (int i = 0; i < DYNAMIC_OBJECT_CNT; i++)
        {
            _scene2D.Remove_DynamicObject2D(&_obj[i]);

        #ifdef DEBUG_ENABLED
            _startTime = std::chrono::high_resolution_clock::now();
        #endif

            _obj[i].Move_TowardsTarget(_target.x, _target.y, _map);

        #ifdef DEBUG_ENABLED
            _duration += std::chrono::high_resolution_clock::now() - _startTime;
        #endif

            _scene2D.Add_DynamicObject2D(&_obj[i]);
        }

    #ifdef DEBUG_ENABLED
        std::cout << "Number of objects: " << DYNAMIC_OBJECT_CNT << " | Time taken: " << _duration.count() << "s" << std::endl;
    #endif



        _scene2D.Set_CustomValue(_target.x, _target.y, COLOR_YELLOW_NUMBER);
        _scene2D.Print();
        _scene2D.Remove_CustomValue(_target.x, _target.y, COLOR_YELLOW_NUMBER);

        (void)std::getchar();
        system("cls");
    }

    delete[] _obj;

    return 0;
}



void Draw_Scene(Scene2D& _scene2D)
{
    _scene2D.Draw_Line(StartPoint(0, 0), EndPoint(39, 0), COLOR_STATIC_NUMBER);
    _scene2D.Draw_Line(StartPoint(0, 39), EndPoint(39, 39), COLOR_STATIC_NUMBER);
    _scene2D.Draw_Line(StartPoint(0, 0), EndPoint(0, 39), COLOR_STATIC_NUMBER);
    _scene2D.Draw_Line(StartPoint(39, 0), EndPoint(39, 39), COLOR_STATIC_NUMBER);

    _scene2D.Draw_Line(StartPoint(17, 10), EndPoint(17, 19), COLOR_STATIC_NUMBER);
    _scene2D.Draw_Line(StartPoint(17, 24), EndPoint(17, 30), COLOR_STATIC_NUMBER);
    _scene2D.Draw_Line(StartPoint(21, 10), EndPoint(30, 10), COLOR_STATIC_NUMBER);

    _scene2D.Draw_Square(StartPoint(4, 4), EndPoint(8, 8), COLOR_STATIC_NUMBER);
}