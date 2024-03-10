#include "parser_Math.h"
#include "StringCommandParser.h"

#include <iostream>
#include <string>



CMD_RESULT Parser_Math::Parse(const std::string& expression, CommandData_t& outCommandData)
{
	CMD_RESULT _return = CMD_RESULT::INPUT_INVALID;
	std::string _command;



	if (expression != "")
	{
		// Check if Command can be extracted: 
		size_t _position = expression.find(' ');

		if (_position == -1)
		{
			_command = expression;
			_position = 0;
		}
		else
		{
			_command = expression.substr(0, _position);
		}


		// If command not found - try calculate math expression:
		auto _foundCommand = commands.find(_command);

		if (_foundCommand != commands.end())
		{
			std::string _arg = expression.substr(_position, expression.length());
			_return = _foundCommand->second->Execute(_arg, outCommandData);
		}
		else
		{
			double _mathResult;

			_return = stringMathParser.Calculate_Expression(expression, _mathResult);

			if (_return == CMD_RESULT::RESULT_CORRECT) {
				outCommandData.result = " = " + std::to_string(_mathResult) + '\n';
			}
			else {
				outCommandData.result = "ERROR: Invalid expression\n";
			}
		}
	}
	else 
	{
		CMD_RESULT _return = CMD_RESULT::EMPTY;
	}


	return _return;
}



void Parser_Math::Clear_UsedVariables()
{
	stringMathParser.Clear_Variables();
}

void Parser_Math::Reparse_LastExpression(char variableName, CommandData_t& outCommandData)
{
	for (float currentValue = -50.0f; currentValue < 50.0f; currentValue += 0.1f)
	{
		double _result;

		stringMathParser.Recalculate(variableName, currentValue, _result);
		outCommandData.vector_float.push_back((float)_result);
	}
}