#pragma once

#include "Parser_Base.h"
#include "StringCommandParser.h"



class Command_Text : public Parser_Base
{

private:

    const size_t parameters_Cnt = 3;



public:

    Command_Text() {}
    ~Command_Text() {}



    std::string Get_Description() override {
        return "Draw Text [Index Point.x Point.y Text]";
    }

    CMD_RESULT Execute(const std::string& args, CommandData_t& outCommandData) override;

};