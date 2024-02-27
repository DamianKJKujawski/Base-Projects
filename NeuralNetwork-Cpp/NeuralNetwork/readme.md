
## Project use:

    The project task was to:
     -  Recognize simple images
     -  Identify sounds through harmonic analysis
     -  Organize measurement data





## Project Structure:

    project-root/
    │
    ├── src/
    │	│
    │	├── main.cpp
    │	│
    │	├── main-NeuralNetwork/
    │	│	│
    │	│	├── NeuralNetwork_FeedForward.h
    │	│	├── NeuralNetwork_FeedForward.cpp
    │	│	│
    │	│	└── NeuralNetwork_Builder.h					<!-- Builder pattern for NeuralNetwork_FeedForward --!>
    │	│
    │	└── GLOBAL/
    │		│
    │		├── Define.h
    │		├── Project.h                               <!-- Project info --!>
    │		└── Struct.h                                <!-- TrainingData_t struct --!>
    │
    └── README.md





## How to use NeuralNetwork:

    (...)

    NeuralNetwork_Builder _neuralNetwork_Builder;
    NeuralNetwork_FeedForward _neuralNetwork = _neuralNetwork_Builder
        .Set_Size_InputNodes()
        .Set_Size_HiddenNodes()
        .Set_Size_OutputNodes()
        .Set_LearningRate()
        .Build();

    // Step 1: Create training data:
    TrainingData_t _trainingData
    {
        {
            {trainingData},
        },
        {
            {result}, 
        }
    };

    // Step 2: Train Neural Network:
    UseL _neuralNetwork.Train(inputData, targetData);

    // Step 3: Create test data:
    std::vector<std::vector<double>> _testingInputs = 
    {
        {testData},
    };

    // 4. Test the Neural Network with different input vectors
    std::vector<double> _output = _neuralNetwork.FeedForward(_testingInput);