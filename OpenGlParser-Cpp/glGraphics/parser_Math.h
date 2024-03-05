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
#include "parser_Graph.h"



class Parser_Math : Parser_Equations
{

private:

	std::map<std::string, std::unique_ptr<Parser_CMD>> commands;

	std::unordered_map<char, double> variables;

	std::string previousExpression;



	bool IsOperator(char c);
	int  Precedence(char op);
	void ApplyOperation(std::stack<double>& numbers, std::stack<char>& operators);

	std::string RemoveEmptySpaces(const std::string& expression);



public:

    Parser_Math()
    {
        // Add commands to the map
		commands["graph"] = std::make_unique<Parser_Graph>();

        commands["help"] = std::make_unique<Parser_Help>(commands);

        commands["exit"] = std::make_unique<Parser_Exit>();

        commands["cmd"] = std::make_unique<Parser_Switch_Command>();
    }



	CMD_RESULT Parse(const std::string& expression, double& result, std::vector<float>& outputVector_f, std::vector<std::string>& outputVector_s) override;
	CMD_RESULT Parse_Math(const std::string& expression, double& result);

	bool Recalculate(char variable, double value, double& result);



};

#endif