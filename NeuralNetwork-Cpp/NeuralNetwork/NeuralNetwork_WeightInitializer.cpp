#pragma once

#include "NeuralNetwork_WeightInitializer.h"



#pragma region PUBLIC:

    // Get a random weight value between -1 and 1
    double NeuralNetwork_WeightInitializer::Get_RandomWeight()
    {
        return ((double)rand() / RAND_MAX) * 2 - 1;
    }

    void NeuralNetwork_WeightInitializer::Randomize_Weights(std::vector<std::vector<double>>& weights, int size_nodes, int size_furtherNodes)
    {
        for (int i = 0; i < size_nodes; ++i)
        {
            for (int j = 0; j < size_furtherNodes; ++j)
            {
                weights[i][j] = NeuralNetwork_WeightInitializer::Get_RandomWeight();
            }
        }
    }

#pragma endregion