#pragma once

#include "NeuralNetwork_FeedForward.h"



class NeuralNetwork_Builder
{

private:

    NeuralNetwork_FeedForward* neuralNetwork;



public:

    NeuralNetwork_Builder() : neuralNetwork(new NeuralNetwork_FeedForward()) {}
    ~NeuralNetwork_Builder() { delete neuralNetwork; }



    NeuralNetwork_Builder* Set_Size_InputNodes(int size_input);
    NeuralNetwork_Builder* Set_Size_HiddenNodes(int size_hidden);
    NeuralNetwork_Builder* Set_Size_OutputNodes(int size_output);
    NeuralNetwork_Builder* Set_LearningRate(double learningRate);

    NeuralNetwork_FeedForward* Build();

};