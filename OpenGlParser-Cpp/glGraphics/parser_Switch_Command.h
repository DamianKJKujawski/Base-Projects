#pragma once

#include "Parser_Base.h"



class Parser_Switch_Command : public Parser_Base
{

public:

    Parser_Switch_Command() {}
    ~Parser_Switch_Command() {}



    std::string Get_Description() override {
        return "Switch to Command Parser";
    }

    CMD_RESULT Execute(const std::string& args, CommandData_t& outCommandData) override;

};
