#pragma once

#include "StringMathTokenizer.h"



class StringMathParser
{

private:

    std::unordered_map<char, double> variables;
    std::string expressionPrevious;



public:

    CMD_RESULT Calculate_Expression(const std::string& expression, double& outResult);

    void Clear_Variables();
    bool Recalculate(char variableName, double variableValue, double& result);

};

