#ifndef DYNAMIC_OBJECT2D_FAST_H
#define DYNAMIC_OBJECT2D_FAST_H

    #include "DynamicObject2D.h"



    // Avoid diamond inheritance -> Compiler adds an extra pointer to the array of inheriting classes -> Leads to high memory overhead
    // But... In this case, more memory was used, but the compiler managed to achieve better performance:

    class DynamicObject2D_Fast : public DynamicObject2D
    {

    private:

        int x;
        int y;

        int moveRotationDirection;

        int vector_x;
        int vector_y;

        bool rotationEnabled = false;



        void Randomize_DirectionVector();

        inline void Rotate_DirectionVector(int& x, int& y) noexcept;
        inline void Switch_RotationDirection() noexcept;

        inline bool Is_NewPositionNotBlocked(int x, int y, const int map[SCENE_WIDTH][SCENE_HEIGHT]) noexcept;
        inline void Update_CurrentPosition(int new_x, int new_y) noexcept;



    public:

        DynamicObject2D_Fast();

        int var_x() const override {
            return x;
        }
        int var_y() const override {
            return y;
        }



        bool Move_TowardsTarget(const int& target_x, const int& target_y, int map[SCENE_WIDTH][SCENE_HEIGHT]) noexcept override;

    };



#endif // DYNAMIC_OBJECT2D_FAST_H