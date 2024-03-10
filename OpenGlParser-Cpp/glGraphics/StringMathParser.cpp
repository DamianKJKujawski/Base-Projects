#include "StringMathParser.h"



CMD_RESULT StringMathParser::Calculate_Expression(const std::string& expression, double& outResult)
{
    CMD_RESULT _return = CMD_RESULT::RESULT_CORRECT;

    std::string _exp = StringCommandParser::Remove_EmptySpaces(expression);
    std::stack<double> _numbers;
    std::stack<char> _operators;


    // Step 1: Tokenize string:
    for (size_t i = 0; i < _exp.length(); ++i)
    {
        if (_exp[i] == ' ')
            continue;

        // Number:
        if (isdigit(_exp[i]))
        {
            StringMathTokenizer::Convert_StringToNumber(_exp, i, _numbers);
        }
        // Parenthese:
        else if (_exp[i] == '(')
        {
            _operators.push(_exp[i]);
        }
        else if (_exp[i] == ')')
        {
            StringMathTokenizer::Process_Parenthese(_numbers, _operators);
        }
        // Operator:
        else if (StringMathTokenizer::Is_Operator(_exp[i]))
        {
            StringMathTokenizer::Process_Operator(_exp[i], _numbers, _operators);
        }
        // Trigonometry:
        else if ((_exp[i] == 's'  && _exp[i + 1] == 'i' && _exp[i + 2] == 'n') && i + 2 < _exp.length())
        {
            StringMathTokenizer::Process_TrigonometricFunction(_exp, i, _operators);
        }
        else if ((_exp[i] == 'c' && _exp[i + 1] == 'o' && _exp[i + 2] == 's') && i + 2 < _exp.length())
        {
            StringMathTokenizer::Process_TrigonometricFunction(_exp, i, _operators);
        }
        // Variable:
        else if (isalpha(_exp[i]))
        {
            if (!StringMathTokenizer::Handle_Variable(variables, _exp[i], _numbers)) 
            {
                _return = CMD_RESULT::INPUT_INVALID;
                break;
            }
        }
    }


    // Step 2: Calculate parsed expression:
    while (!_operators.empty())
    {
        StringMathTokenizer::Apply_Operation(_numbers, _operators);
    }


    // Step 3: Check if expression was valid:
    if (_numbers.empty())
    {
        if (expression == "")
            _return = CMD_RESULT::EMPTY;
        else
            _return = CMD_RESULT::INPUT_INVALID;
    }
    else
    {
        // Step 4: Set result if valid:
        outResult = _numbers.top();
        expressionPrevious = expression;
    }

    return _return;
}



void StringMathParser::Clear_Variables()
{
    variables.clear();
}

// Recalculate the previous expression if it was correct
bool StringMathParser::Recalculate(char variableName, double variableValue, double& result)
{
    if (variables.find(variableName) != variables.end())
    {
        variables[variableName] = variableValue;
        StringMathParser::Calculate_Expression(expressionPrevious, result);

        return true;
    }
    else
        return false;
}
