#include "parser_Math.h"

CMD_RESULT Parser_Math::Parse(const std::string& expression, double& result, std::vector<float>& outputVector_f, std::vector<std::string>& outputVector_s)
{
	CMD_RESULT _result = CMD_RESULT::INVALID;

	size_t _position = expression.find(' ');

	std::string _command;
	std::string _arg;

	if (_position == -1)
		_command = expression;
	else
	{
		_command = expression.substr(0, _position);
		_arg = expression.substr(_position, expression.length() - 1);
	}

	auto _foundCommand = commands.find(_command);

	if (_foundCommand != commands.end())
	{
		_result = _foundCommand->second->Execute(_arg, outputVector_f, outputVector_s);
	}
	else
	{
		_result = Parser_Math::Parse_Math(expression, result);
	}

	return _result;
}

CMD_RESULT Parser_Math::Parse_Math(const std::string& expression, double& result)
{
	std::string _exp = RemoveEmptySpaces(expression);
	std::stack<double> _numbers;
	std::stack<char> _operators;

	for (size_t i = 0; i < _exp.length(); ++i)
	{
		char _c = _exp[i];

		if (_c == ' ')
			continue;

		if (isdigit(_c))
		{
			double _num = 0;

			while (i < _exp.length() && (isdigit(_exp[i]) || _exp[i] == '.'))
			{
				_num = _num * 10 + (double)((char)_exp[i] - (char)'0');
				++i;
			}
			--i;

			_numbers.push(_num);
		}
		else if (_c == '(')
		{
			_operators.push(_c);
		}
		else if (_c == ')')
		{
			while (_operators.top() != '(')
			{
				ApplyOperation(_numbers, _operators);
			}

			_operators.pop(); // Remove '('
		}
		else if (IsOperator(_c))
		{
			while (!_operators.empty() && Precedence(_operators.top()) >= Precedence(_c))
			{
				ApplyOperation(_numbers, _operators);
			}

			_operators.push(_c);
		}
		else if (_c == 's' && i + 2 < _exp.length() && _exp[i + 1] == 'i' && _exp[i + 2] == 'n')
		{
			_operators.push(_c);

			i += 2;
		}
		else if (_c == 'c' && i + 2 < _exp.length() && _exp[i + 1] == 'o' && _exp[i + 2] == 's')
		{
			_operators.push(_c);

			i += 2;
		}
		else if (isalpha(_c)) // Variable handling
		{
			if (variables.find(_c) != variables.end())
			{
				_numbers.push(variables[_c]);
			}
			else if (_c == 'x' || _c == 'X')
			{
				std::cout << "Enter value for variable " << _c << ": ";

				double _val;

				std::cin >> _val;

				if (std::cin.good()) 
				{
					variables[_c] = _val;

					_numbers.push(_val);
				}
			}
			else 
			{
				std::cerr << "Invalid variable: " << _c << std::endl;

				return CMD_RESULT::INVALID;
			}
		}
	}

	while (!_operators.empty())
	{
		ApplyOperation(_numbers, _operators);
	}

	if (_numbers.empty())
	{
		result = 0;

		if (expression == "")
			return CMD_RESULT::EMPTY;
		else
			return CMD_RESULT::INVALID;
	}

	result = _numbers.top();
	this->previousExpression = expression;

	return CMD_RESULT::CORRECT;
}

bool Parser_Math::Recalculate(char variable, double value, double& result)
{
	if (variables.find(variable) != variables.end()) 
	{
		variables[variable] = value;
		Parser_Math::Parse_Math(this->previousExpression, result);

		return true;
	}
	else {
		return false;
	}
}



bool Parser_Math::IsOperator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int Parser_Math::Precedence(char op)
{
	if (op == '+' || op == '-')
		return 1;

	if (op == '*' || op == '/')
		return 2;

	if (op == 's' || op == 'c')
		return 3;

	return 0;
}

void Parser_Math::ApplyOperation(std::stack<double>& numbers, std::stack<char>& operators)
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

std::string Parser_Math::RemoveEmptySpaces(const std::string& expression)
{
	std::string exp;

	for (char c : expression)
	{
		if (c != ' ')
			exp += c;
	}

	return exp;
}
