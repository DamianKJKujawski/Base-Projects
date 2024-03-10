#ifndef MATH_PARSER_HPP
#define MATH_PARSER_HPP

#include <iostream>
#include <unordered_map>

#include "StringMathParser.h"
#include "command_Help.h"
#include "command_Exit.h"
#include "parser_Switch_Command.h"
#include "parser_Graph.h"
#include "parser_Clear.h"



class Parser_Math
{

private:

	std::map<std::string, std::unique_ptr<Parser_Base>> commands;

	StringMathParser stringMathParser;



public:

    Parser_Math()
    {
		commands["graph"] = std::make_unique<Parser_Graph>();
		commands["clear"] = std::make_unique<Parser_Clear>();

		commands["help"] = std::make_unique<Command_Help>(commands);
        commands["cmd"] = std::make_unique<Parser_Switch_Command>();
		commands["exit"] = std::make_unique<Command_Exit>();
    }



	CMD_RESULT Parse(const std::string& expression, CommandData_t& outCommandData);

	void Clear_UsedVariables();
	void Reparse_LastExpression(char variableName, CommandData_t& outCommandData);

};

#endif