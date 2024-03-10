#pragma once

#include "StringCommandParser.h"
#include "CMD.h"

#include <stack>
#include <cmath>
#include <unordered_map>



class StringMathTokenizer
{
    enum MATH_OPERATOR
    {
        ADD_SUBTRACT = 1,
        MULTIPLY_DIVIDE,
        TRIG_FUNCTION,
        DEFAULT = 0
    };



public:

    static bool Is_Operator(char c);
    static MATH_OPERATOR OperatorPrecedence(char op);

    static void Apply_Operation(std::stack<double>& numbers, std::stack<char>& operators);
    static bool Handle_Variable(std::unordered_map<char, double>& variables, char variableName, std::stack<double>& numbers);
    static void Convert_StringToNumber(const std::string& expression, size_t& offset, std::stack<double>& numbers);

    static void Process_Parenthese(std::stack<double>& numbers, std::stack<char>& operators);
    static void Process_Operator(char character, std::stack<double>& numbers, std::stack<char>& operators);
    static void Process_TrigonometricFunction(const std::string& expression, size_t& offset, std::stack<char>& operators);

};

