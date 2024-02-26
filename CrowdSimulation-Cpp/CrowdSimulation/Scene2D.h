#ifndef SCENE_H
#define SCENE_H

    #include <iostream>

    #include "DynamicObject2D.h"



    class Scene2D
    {

    private:

        int(*map)[SCENE_WIDTH][SCENE_HEIGHT];



    public:

        Scene2D(int(*map)[SCENE_WIDTH][SCENE_HEIGHT]);
        ~Scene2D();



        void Set_CustomValue(int x, int y, int value);
        void Remove_CustomValue(int x, int y, int value);

        void Draw_Line(StartPoint startPoint, EndPoint endPoint, int value);
        void Draw_Square(StartPoint startPoint, EndPoint endPoint, int value);

        void Add_DynamicObject2D(const DynamicObject2D* object2D);
        void Remove_DynamicObject2D(const DynamicObject2D* object2D);

        void Print();

    };

#endif // SCENE_H