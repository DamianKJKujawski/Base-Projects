#pragma once

#include "NeuralNetwork_LayerErrors.h"



#pragma region PUBLIC:

    std::vector<double> NeuralNetwork_LayerErrors::Calculate_OutputLayerErrors(std::vector<double> output, int size_outputNodes, const std::vector<double>& target)
    {
        std::vector<double> _outputErrors(size_outputNodes);

        for (int i = 0; i < size_outputNodes; ++i)
        {
            _outputErrors[i] = (target[i] - output[i]) * output[i] * (1 - output[i]);
        }

        return _outputErrors;
    }

    std::vector<double> NeuralNetwork_LayerErrors::Calculate_HiddenLayerErrors(std::vector<double> outputErrors, int size_hiddenNodes, int size_outputNodes, std::vector<double> hiddenOutput, std::vector<std::vector<double>> weights_hiddenToOutput)
    {
        std::vector<double> _hiddenErrors(size_hiddenNodes);

        for (int i = 0; i < size_hiddenNodes; ++i)
        {
            double _error = 0;
            for (int j = 0; j < size_outputNodes; ++j)
            {
                _error += outputErrors[j] * weights_hiddenToOutput[i][j];
            }
            _hiddenErrors[i] = _error * hiddenOutput[i] * (1 - hiddenOutput[i]);
        }

        return _hiddenErrors;
    }

#pragma endregion