#pragma once

#include "Parser_Base.h"
#include "StringCommandParser.h"



class Command_Line : public Parser_Base
{

private:

    const size_t parameters_Cnt = 5;



public:

    Command_Line() {}
    ~Command_Line() {}



    std::string Get_Description() override {
        return "Draw Line [Index Point1.x Point1.y Point2.x Point2.y]";
    }

    CMD_RESULT Execute(const std::string& args, CommandData_t& outCommandData) override;

};