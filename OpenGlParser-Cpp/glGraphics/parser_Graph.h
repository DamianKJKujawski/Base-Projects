#pragma once

#include "Parser_Base.h"
#include "StringCommandParser.h"



class Parser_Graph : public Parser_Base
{

    const size_t parameters_Cnt = 4;



public:

    Parser_Graph() {}
    ~Parser_Graph() {}



    std::string Get_Description() override {
        return "Draw Graph based on previous Math Expression [Index Point1.x Point1.y Variable]";
    }

    CMD_RESULT Execute(const std::string& args, CommandData_t& outCommandData) override;

};
