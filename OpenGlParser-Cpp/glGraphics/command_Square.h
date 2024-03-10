#pragma once

#include "Parser_Base.h"
#include "StringCommandParser.h"



class Command_Square : public Parser_Base
{

private:

    const size_t parameters_Cnt = 5;



public:

    Command_Square() {}
    ~Command_Square() {}



    std::string Get_Description() override {
        return "Draw Line [Index Point1.x Size.y Size.x Point2.y]";
    }

    CMD_RESULT Execute(const std::string& args, CommandData_t& outCommandData) override;

};