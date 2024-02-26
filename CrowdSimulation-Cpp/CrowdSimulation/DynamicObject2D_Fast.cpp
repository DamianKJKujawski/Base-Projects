#include "DynamicObject2D_Fast.h"
#include "Random.h"



#pragma region PRIVATE:

    DynamicObject2D_Fast::DynamicObject2D_Fast()
    {
        this->x = x_constructor;
        this->y = y_constructor;
        
        Randomize_DirectionVector();
    }



    void DynamicObject2D_Fast::Randomize_DirectionVector()
    {
        moveRotationDirection = Random::Draw_OneOfTwo(1, 4);
    }

    inline void DynamicObject2D_Fast::Rotate_DirectionVector(int& x, int& y) noexcept
    {
        /* ASM EQUIVALENT:
            mov     rax, QWORD PTR [rbp-8]
            mov     edx, DWORD PTR [rax]
            mov     eax, DWORD PTR moveRotation[rip]
            add     edx, eax
            mov     rax, QWORD PTR [rbp-16]
            mov     eax, DWORD PTR [rax]
            add     eax, 1
            movsx   rcx, eax
            movsx   rdx, edx
            mov     rax, rdx
            add     rax, rax
            add     rax, rdx
            add     rax, rcx
            mov     edx, DWORD PTR Rotate_DirectionVector(int&, int&)::_rotationTable[0+rax*8]
            mov     rax, QWORD PTR [rbp-8]
            mov     DWORD PTR [rax], edx
            mov     rax, QWORD PTR [rbp-8]
            mov     edx, DWORD PTR [rax]
            mov     eax, DWORD PTR moveRotation[rip]
            add     edx, eax
            mov     rax, QWORD PTR [rbp-16]
            mov     eax, DWORD PTR [rax]
            add     eax, 1
            movsx   rcx, eax
            movsx   rdx, edx
            mov     rax, rdx
            add     rax, rax
            add     rax, rdx
            add     rax, rcx
            mov     edx, DWORD PTR Rotate_DirectionVector(int&, int&)::_rotationTable[4+rax*8]
            mov     rax, QWORD PTR [rbp-16]
            mov     DWORD PTR [rax], edx
        */

        static const int _rotationTable[6][3][2] =
        {
            {/*-1,-1*/{ 0,-1}, /*-1, 0*/{-1,-1}, /*-1, 1*/{-1, 0}},
            {/* 0,-1*/{ 1,-1},          { 0, 0}, /* 0, 1*/{-1, 1}},
            {/* 1,-1*/{ 1, 0}, /* 1, 0*/{ 1, 1}, /* 1, 1*/{ 0, 1}},
            {/*-1,-1*/{-1, 0}, /*-1, 0*/{-1, 1}, /*-1, 1*/{ 0, 1}},
            {/* 0,-1*/{-1,-1},          { 0, 0}, /* 0, 1*/{ 1, 1}},
            {/* 1,-1*/{ 0,-1}, /* 1, 0*/{ 1,-1}, /* 1, 1*/{ 1, 0}}
        };

        // Set new value from _rotationTable:
        x = _rotationTable[x + moveRotationDirection][y + 1][0];
        y = _rotationTable[x + moveRotationDirection][y + 1][1];
    }

    inline void DynamicObject2D_Fast::Switch_RotationDirection() noexcept
    {
        /* ASM EQUIVALENT:
            mov     eax, DWORD PTR moveRotation[rip]
            xor     eax, 5
            mov     DWORD PTR moveRotation[rip], eax
        */

        // Allow to switch between 1 and 4 used in DynamicObject2D::Rotate_DirectionVector:
        static const int _rotationTable_ShiftNumber = 5;

        // 1- Rotate right / 4 - Rotate left:
        moveRotationDirection ^= _rotationTable_ShiftNumber;
    }

    // Determine if move possible:
    inline bool DynamicObject2D_Fast::Is_NewPositionNotBlocked(int x, int y, const int map[SCENE_WIDTH][SCENE_HEIGHT]) noexcept
    {
        return map[x][y] == 0;
    }

    inline void DynamicObject2D_Fast::Update_CurrentPosition(int new_x, int new_y) noexcept
    {
        x = new_x;
        y = new_y;
    }

#pragma endregion



#pragma region PUBLIC:

    bool DynamicObject2D_Fast::Move_TowardsTarget(const int& target_x, const int& target_y, int map[SCENE_WIDTH][SCENE_HEIGHT]) noexcept
    {
        // Calculate x/y object-target distance:
        int _delta_x = target_x - x;
        int _delta_y = target_y - y;

        // If distance is 0 break execution:
        if (_delta_x == 0 && _delta_y == 0)
            return true;



        if (rotationEnabled)
        {
            Rotate_DirectionVector(vector_x, vector_y);

            // Determine new position:
            int _new_x = x + vector_x;
            int _new_y = y + vector_y;

            if (Is_NewPositionNotBlocked(_new_x, _new_y, map))
            {
                Update_CurrentPosition(_new_x, _new_y);

                rotationEnabled = false;
            }

            return false;
        }



        // Determine new position:
        vector_x = ((_delta_x > 0) - (_delta_x < 0));
        vector_y = ((_delta_y > 0) - (_delta_y < 0));

        int _new_x = vector_x + x;
        int _new_y = vector_y + y;

        if (Is_NewPositionNotBlocked(_new_x, _new_y, map))
        {
            Update_CurrentPosition(_new_x, _new_y);
            Switch_RotationDirection();

            return false;
        }

        rotationEnabled = true;



        return false;
    }

#pragma endregion