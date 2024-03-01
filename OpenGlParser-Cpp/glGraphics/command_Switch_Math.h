#pragma once

#include "Parser_CMD.h"



class Command_Switch_Math : public Parser_CMD
{

public:

    CMD_RESULT Execute(const std::string& args) override
    {
        std::cout << "MATH Parser: " << args << "\n";

        return CMD_RESULT::CMD_SWITCH_TO_MATH_PARSER;
    }

};
