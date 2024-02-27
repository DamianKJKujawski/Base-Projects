#pragma once

#include <cmath>



class NeuralNetwork_ActivationFunction
{

public:

    static double Sigmoid(double x) 
    {
        return 1 / (1 + exp(-x));
    }

};