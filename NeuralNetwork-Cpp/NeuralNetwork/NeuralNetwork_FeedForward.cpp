#include "NeuralNetwork_FeedForward.h"

#include "NeuralNetwork_ActivationFunction.h"
#include "NeuralNetwork_WeightInitializer.h"
#include "NeuralNetwork_FeedForwardCalculator.h"
#include "NeuralNetwork_LayerErrors.h"



#pragma region PUBLICL:

    void NeuralNetwork_FeedForward::Build()
    {
        // Initialize weights randomly
        weights_inputToHidden.resize(size_inputNodes, std::vector<double>(size_hiddenNodes));
        weights_hiddenToOutput.resize(size_hiddenNodes, std::vector<double>(size_outputNodes));

        // Initialize weights with random values between -1 and 1
        NeuralNetwork_WeightInitializer::Randomize_Weights(weights_inputToHidden, size_inputNodes, size_hiddenNodes);

        NeuralNetwork_WeightInitializer::Randomize_Weights(weights_hiddenToOutput, size_hiddenNodes, size_outputNodes);
    }



    // Feedforward function
    std::vector<double> NeuralNetwork_FeedForward::FeedForward(const std::vector<double>& input) 
    {
        std::vector<double> _hiddenLayerOutput = NeuralNetwork_FeedforwardCalculator::Calculate_HiddenLayerOutputs(input, size_inputNodes, size_hiddenNodes, weights_inputToHidden);

        return NeuralNetwork_FeedforwardCalculator::Calculate_OutputLayerOutputs(_hiddenLayerOutput, size_hiddenNodes, size_outputNodes, weights_hiddenToOutput);
    }

    // Train the neural network using backpropagation
    void NeuralNetwork_FeedForward::Train(const std::vector<double>& input, const std::vector<double>& target)
    {
        // Feedforward:
        std::vector<double> _hiddenOutput = NeuralNetwork_FeedforwardCalculator::Calculate_HiddenLayerOutputs(input, size_inputNodes, size_hiddenNodes, weights_inputToHidden);

        std::vector<double> _output = NeuralNetwork_FeedforwardCalculator::Calculate_OutputLayerOutputs(_hiddenOutput, size_hiddenNodes, size_outputNodes, weights_hiddenToOutput);

        // Backpropagation:
        std::vector<double> _outputErrors = NeuralNetwork_LayerErrors::Calculate_OutputLayerErrors(_output, size_outputNodes, target);

        // Update weights between hidden and output layer
        for (int i = 0; i < size_hiddenNodes; ++i)
        {
            for (int j = 0; j < size_outputNodes; ++j)
            {
                weights_hiddenToOutput[i][j] += learningRate * _outputErrors[j] * _hiddenOutput[i];
            }
        }

        std::vector<double> _hiddenErrors = NeuralNetwork_LayerErrors::Calculate_HiddenLayerErrors(_outputErrors, size_hiddenNodes, size_outputNodes, _hiddenOutput, weights_hiddenToOutput);

        // Update weights between input and hidden layer
        for (int i = 0; i < size_inputNodes; ++i)
        {
            for (int j = 0; j < size_hiddenNodes; ++j)
            {
                weights_inputToHidden[i][j] += learningRate * _hiddenErrors[j] * input[i];
            }
        }
    }

#pragma endregion