#pragma once

#include "Parser_Base.h"



class Command_Help : public Parser_Base
{

private:

    std::map<std::string, std::unique_ptr<Parser_Base>>& commands;



public:

    Command_Help(std::map<std::string, std::unique_ptr<Parser_Base>>& cmds) : commands(cmds) {}
    ~Command_Help() {}



    std::string Get_Description() override {
        return "Display available commands";
    }

    CMD_RESULT Execute(const std::string& args, CommandData_t& outCommandData) override;

};