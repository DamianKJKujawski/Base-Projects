#ifndef STRUCT_H
#define STRUCT_H



    typedef struct Object2D
    {
        int x;
        int y;

        Object2D(int _x, int _y) : x(_x), y(_y) {}

    } Object2D;

    typedef Object2D EndPoint;
    typedef Object2D StartPoint;



#endif // STRUCT_H