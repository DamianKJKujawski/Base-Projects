#include "Random.h"



#pragma region PUBLIC:

    int Random::Draw_OneOfTwo(int a, int b)
    {
        std::random_device _rd;
        std::mt19937 _gen(_rd());
        std::uniform_int_distribution<> _dis(0, 1);
        int _randomNumber = _dis(_gen);

        return (_randomNumber == 0) ? a : b;
    }

#pragma endregion


