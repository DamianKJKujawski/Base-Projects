#include "StringMathTokenizer.h"



bool StringMathTokenizer::Is_Operator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

StringMathTokenizer::MATH_OPERATOR StringMathTokenizer::OperatorPrecedence(char op)
{
    if (op == '+' || op == '-')
        return MATH_OPERATOR::ADD_SUBTRACT;
    if (op == '*' || op == '/')
        return MATH_OPERATOR::MULTIPLY_DIVIDE;
    if (op == 's' || op == 'c')
        return MATH_OPERATOR::TRIG_FUNCTION;

    return MATH_OPERATOR::DEFAULT;
}

void StringMathTokenizer::Apply_Operation(std::stack<double>& numbers, std::stack<char>& operators)
{
    char _op = operators.top();
    operators.pop();

    if (_op == 's')
    {
        double _val = numbers.top();

        numbers.pop();
        numbers.push(sin(_val));
    }
    else if (_op == 'c')
    {
        double _val = numbers.top();

        numbers.pop();
        numbers.push(cos(_val));
    }
    else
    {
        double _b = numbers.top();
        numbers.pop();

        double _a = numbers.top();
        numbers.pop();

        double _result = 0;

        switch (_op)
        {
        case '+':
            _result = _a + _b;
            break;
        case '-':
            _result = _a - _b;
            break;
        case '*':
            _result = _a * _b;
            break;
        case '/':
            _result = _a / _b;
            break;
        }

        numbers.push(_result);
    }
}

bool StringMathTokenizer::Handle_Variable(std::unordered_map<char, double>& variables, char variableName, std::stack<double>& numbers)
{
    if (variables.find(variableName) != variables.end())
    {
        numbers.push(variables[variableName]);
    }
    else if (variableName == 'x' || variableName == 'X')
    {
        std::cout << "Enter value for variable " << variableName << ": ";

        std::string _inputValue;
        std::getline(std::cin, _inputValue);
        double _val = std::stod(_inputValue);

        if (std::cin.good())
        {
            variables[variableName] = _val;

            numbers.push(_val);
        }
    }
    else {
        return false;
    }

    return true;
}

void StringMathTokenizer::Convert_StringToNumber(const std::string& expression, size_t& offset, std::stack<double>& numbers)
{
    double _num = 0;

    while (offset < expression.length() && (isdigit(expression[offset]) || expression[offset] == '.'))
    {
        _num = _num * 10 + (double)(((int)expression[offset]) - ((int)'0'));
        ++offset;
    }
    --offset;

    numbers.push(_num);
}

void StringMathTokenizer::Process_Parenthese(std::stack<double>& numbers, std::stack<char>& operators)
{
    while (operators.top() != '(')
    {
        Apply_Operation(numbers, operators);
    }
    operators.pop(); // Remove '('
}

void StringMathTokenizer::Process_Operator(char character, std::stack<double>& numbers, std::stack<char>& operators)
{
    while (!operators.empty() && StringMathTokenizer::OperatorPrecedence(operators.top()) >= StringMathTokenizer::OperatorPrecedence(character))
    {
        Apply_Operation(numbers, operators);
    }
    operators.push(character);
}

void StringMathTokenizer::Process_TrigonometricFunction(const std::string& expression, size_t& offset, std::stack<char>& operators)
{
    operators.push(expression[offset]);
    offset += 2;
}