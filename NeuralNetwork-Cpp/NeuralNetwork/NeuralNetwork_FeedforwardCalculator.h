#pragma once

#include "NeuralNetwork_ActivationFunction.h"

#include <vector>



class NeuralNetwork_FeedforwardCalculator
{

public:

    static std::vector<double> Calculate_HiddenLayerOutputs ( 
        const std::vector<double>& input, int size_inputNodes, int size_hiddenNodes, std::vector<std::vector<double>> weights_inputToHidden);

    static std::vector<double> Calculate_OutputLayerOutputs (
        const std::vector<double>& hiddenLayerOutput, int size_hiddenNodes, int size_outputNodes, std::vector<std::vector<double>> weights_hiddenToOutput);

};