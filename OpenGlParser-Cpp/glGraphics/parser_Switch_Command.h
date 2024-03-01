#pragma once
#pragma once

#include "Parser_CMD.h"



class Parser_Switch_Command : public Parser_CMD
{

public:

    CMD_RESULT Execute(const std::string& args) override
    {
        std::cout << "CMD Parser: " << args << "\n";

        return CMD_RESULT::CMD_SWITCH_TO_COMMAND_PARSER;
    }

};
