#pragma once

#include "Parser_Base.h"
#include "StringCommandParser.h"



class Command_Remove : public Parser_Base
{

private:

    const size_t parameters_Cnt = 1;



public:

    Command_Remove() {}
    ~Command_Remove() {}



    std::string Get_Description() override {
        return "Remove Object [Index]";
    }

    CMD_RESULT Execute(const std::string& args, CommandData_t& outCommandData) override;

};