#pragma once

#include "Parser_CMD.h"



class Command_Switch_Math : public Parser_CMD
{

public:

    CMD_RESULT Execute(const std::string& args, std::vector<float>& outputVector_f, std::vector<std::string>& outputVector_s) override
    {
        std::cout << "MATH Parser: " << args << "\n";

        return CMD_RESULT::CMD_SWITCH_TO_MATH_PARSER;
    }

};
