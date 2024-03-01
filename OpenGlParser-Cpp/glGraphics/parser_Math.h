#ifndef MATH_PARSER_HPP
#define MATH_PARSER_HPP



#include <iostream>
#include <stack>
#include <cmath>
#include <unordered_map>

#include "Parser_Equations.h"

#include "parser_Switch_Command.h"
#include "parser_Help.h"
#include "parser_Exit.h"



class Parser_Math : Parser_Equations
{

private:

	std::map<std::string, std::unique_ptr<Parser_CMD>> commands;

	std::string previousEquation;
	std::unordered_map<char, double> variables;


	bool IsOperator(char c);
	int  Precedence(char op);
	void ApplyOperation(std::stack<double>& numbers, std::stack<char>& operators);

	std::string RemoveEmptySpaces(const std::string& expression);



public:

    Parser_Math()
    {
        // Add commands to the map
        commands["help"] = std::make_unique<Parser_Help>(commands);

        commands["exit"] = std::make_unique<Parser_Exit>();

        commands["cmd"] = std::make_unique<Parser_Switch_Command>();
    }



	CMD_RESULT Parse(const std::string& expression, double& result);
	CMD_RESULT Parse_Math(const std::string& expression, double& result);

};

#endif