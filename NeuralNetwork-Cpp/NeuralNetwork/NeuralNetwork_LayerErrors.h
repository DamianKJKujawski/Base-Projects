#pragma once

#include <vector>



class NeuralNetwork_LayerErrors
{

public:

    static std::vector<double> Calculate_OutputLayerErrors(std::vector<double> output, int size_outputNodes, const std::vector<double>& target);

    static std::vector<double> Calculate_HiddenLayerErrors (
        std::vector<double> outputErrors, int size_hiddenNodes, int size_outputNodes, 
        std::vector<double> hiddenOutput, std::vector<std::vector<double>> weights_hiddenToOutput
    );

};