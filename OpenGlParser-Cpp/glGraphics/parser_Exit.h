#pragma once

#include "Parser_CMD.h"



class Parser_Exit : public Parser_CMD
{

public:

    CMD_RESULT Execute(const std::string& args, std::vector<float>& outputVector_f, std::vector<std::string>& outputVector_s) override
    {
        return CMD_RESULT::EXIT;
    }

};
