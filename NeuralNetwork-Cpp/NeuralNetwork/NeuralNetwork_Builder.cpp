#include "NeuralNetwork_Builder.h"



#pragma region PUBLIC:

    NeuralNetwork_Builder* NeuralNetwork_Builder::Set_Size_InputNodes(int size_input)
    {
        neuralNetwork->Set_Size_InputNodes(size_input);

        return this;
    }

    NeuralNetwork_Builder* NeuralNetwork_Builder::Set_Size_HiddenNodes(int size_hidden)
    {
        neuralNetwork->Set_Size_HiddenNodes(size_hidden);

        return this;
    }

    NeuralNetwork_Builder* NeuralNetwork_Builder::Set_Size_OutputNodes(int size_output)
    {
        neuralNetwork->Set_Size_OutputNodes(size_output);

        return this;
    }

    NeuralNetwork_Builder* NeuralNetwork_Builder::Set_LearningRate(double learningRate)
    {
        neuralNetwork->Set_LearningRate(learningRate);

        return this;
    }

    NeuralNetwork_FeedForward* NeuralNetwork_Builder::Build()
    {
        if (neuralNetwork->Check_Build())
        {
            neuralNetwork->Build();
            return neuralNetwork;
        }
        else
        {
            delete neuralNetwork;
            return nullptr;
        }
    }

#pragma endregion