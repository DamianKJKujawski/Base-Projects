#pragma once

#include "parser_Math.h"
#include "parser_Command.h"



class Parser
{

private:

    CMD_RESULT(Parser::* methodPtr)(CommandData_t& outCommandData);

    Parser_Command parser_Command;
    Parser_Math parser_Math;



    CMD_RESULT Parse_Command(CommandData_t& outCommandData);
    CMD_RESULT Parse_MathExpression(CommandData_t& outCommandData);



public:

    Parser() {
        this->methodPtr = &Parser::Parse_Command;
    }

    ~Parser()
    {}



    CMD_RESULT Parse_CMD(CommandData_t& outCommandData);
    void Execute_CMD(CMD_RESULT cmd, CommandData_t& outCommandData);

    void DisplayResult(CommandData_t& outCommandData);

};

