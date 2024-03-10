#pragma once

#include "Parser_Base.h"
#include "StringCommandParser.h"



class Command_Point : public Parser_Base
{

private:

    const size_t parameters_Cnt = 3;



public:

    Command_Point() {}
    ~Command_Point() {}



    std::string Get_Description() override {
        return "Draw Line [Index Point.x Point.y]";
    }

    CMD_RESULT Execute(const std::string& args, CommandData_t& outCommandData) override;

};