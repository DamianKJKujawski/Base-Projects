#pragma once

#include "Parser_Base.h"
#include "StringCommandParser.h"



class Command_Texture : public Parser_Base
{

private:

    const size_t parameters_Cnt = 6;



public:

    Command_Texture() {}
    ~Command_Texture() {}



    std::string Get_Description() override {
        return "Draw Texture [Index Point.x Point.y Size.x Size.y]";
    }

    CMD_RESULT Execute(const std::string& args, CommandData_t& outCommandData) override;

};