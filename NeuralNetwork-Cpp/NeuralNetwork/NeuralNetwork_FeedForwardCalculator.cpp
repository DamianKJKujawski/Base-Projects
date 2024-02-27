#pragma once

#include "NeuralNetwork_FeedForwardCalculator.h"



#pragma region PUBLIC:

    // Calculate hidden layer outputs:
    std::vector<double> NeuralNetwork_FeedforwardCalculator::Calculate_HiddenLayerOutputs(const std::vector<double>& input, int size_inputNodes, int size_hiddenNodes, std::vector<std::vector<double>> weights_inputToHidden)
    {
        std::vector<double> _hiddenOutput(size_hiddenNodes);

        for (int i = 0; i < size_hiddenNodes; ++i)
        {
            double _sum = 0;

            for (int j = 0; j < size_inputNodes; ++j)
            {
                _sum += input[j] * weights_inputToHidden[j][i];
            }

            _hiddenOutput[i] = NeuralNetwork_ActivationFunction::Sigmoid(_sum);
        }

        return _hiddenOutput;
    }

    // Calculate output layer outputs:
    std::vector<double> NeuralNetwork_FeedforwardCalculator::Calculate_OutputLayerOutputs(const std::vector<double>& hiddenLayerOutput, int size_hiddenNodes, int size_outputNodes, std::vector<std::vector<double>> weights_hiddenToOutput)
    {
        std::vector<double> _output(size_outputNodes);

        for (int i = 0; i < size_outputNodes; ++i)
        {
            double _sum = 0;

            for (int j = 0; j < size_hiddenNodes; ++j)
            {
                _sum += hiddenLayerOutput[j] * weights_hiddenToOutput[j][i];
            }

            _output[i] = NeuralNetwork_ActivationFunction::Sigmoid(_sum);
        }

        return _output;
    }

#pragma endregion