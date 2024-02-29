#pragma once

#include "Parser_CMD.h"



class Command_Help : public Parser_CMD
{

private:

    std::map<std::string, std::unique_ptr<Parser_CMD>>& commands;



public:

    Command_Help(std::map<std::string, std::unique_ptr<Parser_CMD>>& cmds) : commands(cmds) {}

    ~Command_Help()
    {}



    CMD_RESULT Execute(const std::string& args) override
    {
        std::cout << "HELP: Available commands: " << args << "\n";

        for (const auto& command : commands)
        {
            std::cout << "- " << command.first << "\n";
        }

        return CMD_RESULT::CORRECT;
    }

};