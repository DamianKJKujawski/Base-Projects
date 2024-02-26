#ifndef DRAWING2D_H
#define DRAWING2D_H

    #include <math.h>

    #include "Config.h"
    #include "Struct.h"



    class Drawing2D
    {

    public:

        static void Draw_BresenhamLine(StartPoint startPoint, EndPoint endPoint, int value, int(*map)[SCENE_WIDTH][SCENE_HEIGHT]);
        static void Draw_Square(StartPoint startPoint, EndPoint endPoint, int value, int(*map)[SCENE_WIDTH][SCENE_HEIGHT]);

    }; 

#endif // DRAWING2D_H