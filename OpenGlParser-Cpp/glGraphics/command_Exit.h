#pragma once

#include "Parser_Base.h"



class Command_Exit : public Parser_Base
{

public:

    Command_Exit() {}
    ~Command_Exit() {}



    std::string Get_Description() override {
        return "Exit program";
    }

    CMD_RESULT Execute(const std::string& args, CommandData_t& outCommandData) override;

};