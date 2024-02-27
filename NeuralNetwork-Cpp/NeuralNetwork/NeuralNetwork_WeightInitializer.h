#pragma once

#include <vector>



class NeuralNetwork_WeightInitializer
{

public:

    static double Get_RandomWeight();

    static void Randomize_Weights(std::vector<std::vector<double>>& weights, int size_inputNodes, int size_hiddenNodes);

};