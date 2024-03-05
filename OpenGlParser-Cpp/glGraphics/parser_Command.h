#pragma once

#include "command_Help.h"
#include "command_Exit.h"
#include "command_Switch_Math.h"
#include "command_Point.h"
#include "command_Line.h"
#include "command_Square.h"
#include "command_Text.h"
#include "command_Load.h"
#include "command_Texture.h"

#include <map>



class Parser_Command
{

private:

    std::map<std::string, std::unique_ptr<Parser_CMD>> commands;



public:

    Parser_Command()
    {
        commands["load"] = std::make_unique<Command_Load>();
        commands["texture"] = std::make_unique<Command_Texture>();

        commands["point"] = std::make_unique<Command_Point>();
        commands["line"] = std::make_unique<Command_Line>();
        commands["square"] = std::make_unique<Command_Square>();
        commands["text"] = std::make_unique<Command_Text>();

        commands["help"] = std::make_unique<Command_Help>(commands);

        commands["exit"] = std::make_unique<Command_Exit>();

        commands["math"] = std::make_unique<Command_Switch_Math>();
    }

    // Execute the command with given name and arguments
    CMD_RESULT Execute(const std::string& cmd, const std::string& args, std::vector<float>& outputVector_f, std::vector<std::string>& outputVector_s)
    {
        CMD_RESULT _resoult = CMD_RESULT::INVALID;

        auto _foundCommand = commands.find(cmd);

        if (_foundCommand != commands.end())
        {
            _resoult = _foundCommand->second->Execute(args, outputVector_f, outputVector_s);
        }

        return _resoult;
    }

};