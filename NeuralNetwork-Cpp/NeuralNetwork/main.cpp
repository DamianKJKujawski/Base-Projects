#include "Struct.h"

#include "NeuralNetwork_Builder.h"



void Test_NeuralNetwork(NeuralNetwork_FeedForward* neuralNetwork, std::vector<std::vector<double>>* testingInputs);
void Train_NeuralNetwork(NeuralNetwork_FeedForward* neuralNetwork, TrainingData_t* trainingData, int iterationsCnt);



int main() 
{
    NeuralNetwork_Builder* _neuralNetwork_Builder = new NeuralNetwork_Builder();
    NeuralNetwork_FeedForward* _neuralNetwork = _neuralNetwork_Builder
        ->Set_Size_InputNodes(10)
        ->Set_Size_HiddenNodes(10)
        ->Set_Size_OutputNodes(1)
        ->Set_LearningRate(0.1)
        ->Build();



    // Step 1: Create training data:
    TrainingData_t _trainingData
    {
        {
            {0.0, 0.25, 0.5, 0.75, 1.0, 0.75, 0.5, 0.25, 0.0, -0.25},   // 1 - Sine
            {0.1, 0.35, 0.6, 0.85, 1.1, 0.85, 0.6, 0.35, 0.1, -0.15},   // 1 - Shifted Sine Wave
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},         // 0
            {0.2, 0.4, 0.6, 0.8, 1.0, 0.8, 0.6, 0.4, 0.2, 0.0},         // 1 - Sine
            {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3}          // 0
        },
        {
            {1}, 
            {1}, 
            {0}, 
            {1}, 
            {0}
        }
    };

    // Step 2: Train Neural Network:
    Train_NeuralNetwork(_neuralNetwork, &_trainingData, 10000);

    // Step 3: Create test data:
    std::vector<std::vector<double>> _testingInputs = 
    {
        {0.05, 0.3, 0.55, 0.8, 1.05, 0.8, 0.55, 0.3, 0.05, -0.2},       // Different Sine Wave pattern
        {0.15, 0.35, 0.55, 0.75, 0.95, 0.75, 0.55, 0.35, 0.15, -0.05},  // Another Different Sine Wave pattern
        {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0}              // Non-Sine Wave pattern
    };

    // 4. Test the Neural Network with different input vectors
    Test_NeuralNetwork(_neuralNetwork, &_testingInputs);



    delete _neuralNetwork_Builder;

    return 0;
}



void Test_NeuralNetwork(NeuralNetwork_FeedForward* neuralNetwork, std::vector<std::vector<double>>* testingInputs)
{
    for (size_t i = 0; i < (*testingInputs).size(); ++i)
    {
        std::vector<double> _input = (*testingInputs)[i];
        std::vector<double> _output = (*neuralNetwork).FeedForward(_input);



        // Print inputs:
        std::cout << "Input: [";

        for (size_t j = 0; j < _input.size(); ++j)
        {
            std::cout << _input[j];
            if (j < _input.size() - 1) std::cout << ", ";
        }



        // Print outputs:
        std::cout << "], Output: " << _output[0];

        if (_output[0] >= 0.5)
        {
            std::cout << " (Sine Wave)" << std::endl;
        }
        else
        {
            std::cout << " (Not Sine Wave)" << std::endl;
        }
    }
}

void Train_NeuralNetwork(NeuralNetwork_FeedForward* neuralNetwork, TrainingData_t* trainingData, int iterationsCnt)
{
    for (int epoch = 0; epoch < iterationsCnt; ++epoch)
    {
        for (size_t i = 0; i < (*trainingData).inputs.size(); ++i)
        {
            std::vector<double> input = (*trainingData).inputs[i];
            std::vector<double> target = (*trainingData).results[i];

            (*neuralNetwork).Train(input, target);
        }
    }
}