#ifndef DYNAMIC_OBJECT2D_H
#define DYNAMIC_OBJECT2D_H

    #include "Config.h"
    #include "Struct.h"
    #include "Define_Colors.h"



    class DynamicObject2D
    {

    protected: 

        static int x_constructor;
        static int y_constructor;

    public:

        static void Set_StartingPoint(const int x, const int y);

        virtual int var_x() const = 0;
        virtual int var_y() const = 0;


   
        virtual bool Move_TowardsTarget(const int& target_x, const int& target_y, int map[SCENE_WIDTH][SCENE_HEIGHT]) noexcept = 0;

    };



#endif // DYNAMIC_OBJECT2D_H