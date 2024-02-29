#ifndef MATH_PARSER_HPP
#define MATH_PARSER_HPP



#include <iostream>
#include <stack>
#include <cmath>
#include <unordered_map>

#include "Parser_Equations.h"



class Parser_Math : Parser_Equations
{

private:

	std::string previousEquation;
	std::unordered_map<char, double> variables;


	bool IsOperator(char c);
	int  Precedence(char op);
	void ApplyOperation(std::stack<double>& numbers, std::stack<char>& operators);

	std::string RemoveEmptySpaces(const std::string& expression);



public:

	CMD_RESULT Parse(const std::string& expression, double& result);

};

#endif