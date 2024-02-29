#pragma once

#include "Parser_CMD.h"



class Command_Exit : public Parser_CMD
{

public:

    CMD_RESULT Execute(const std::string& args) override
    {
        return CMD_RESULT::EXIT;
    }

};