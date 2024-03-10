#pragma once

#include "Parser_Base.h"



class Command_Switch_Math : public Parser_Base
{

public:

    Command_Switch_Math() {}
    ~Command_Switch_Math() {}



    std::string Get_Description() override {
        return "Switch to Math Parser";
    }

    CMD_RESULT Execute(const std::string& args, CommandData_t& outCommandData) override;

};
