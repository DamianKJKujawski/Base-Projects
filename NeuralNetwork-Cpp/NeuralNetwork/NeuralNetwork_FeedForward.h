#pragma once

#include <stdexcept>
#include <iostream>

#include "Struct.h"



class NeuralNetwork_FeedForward
{

private:

    int size_inputNodes = -1; 
    int size_hiddenNodes = -1;
    int size_outputNodes = -1;

    double learningRate = 0.0;
    
    std::vector<std::vector<double>> weights_inputToHidden; // Weights between input and hidden layer
    std::vector<std::vector<double>> weights_hiddenToOutput; // Weights between hidden and output layer



public:

    ~NeuralNetwork_FeedForward() { }



    void Set_Size_InputNodes(int size_input) {
        this->size_inputNodes = size_input;
    }
    void Set_Size_HiddenNodes(int size_hidden) {
        this->size_hiddenNodes = size_hidden;
    }
    void Set_Size_OutputNodes(int size_output) {
        this->size_outputNodes = size_output;
    }
    void Set_LearningRate(double learningRate) {
        this->learningRate = learningRate;
    }

    bool Check_Build() 
    {
        bool _result = false;

        try 
        {
            if (this->size_inputNodes <= 0 || this->size_hiddenNodes <= 0 || this->size_outputNodes <= 0 || this->learningRate <= 0.0) {
                throw std::runtime_error("Invalid NeuralNetwork_FeedForward configuration");
            }
            else {
                _result = true;
            }
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        return _result;
    }

    void Build();



    void Train(const std::vector<double>& input, const std::vector<double>& target);

    std::vector<double> FeedForward(const std::vector<double>& input);
};



