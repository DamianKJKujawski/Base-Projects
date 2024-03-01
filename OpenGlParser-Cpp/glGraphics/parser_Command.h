#pragma once

#include "command_Help.h"
#include "command_Exit.h"
#include "command_Switch_Math.h"

#include <map>



class Parser_Command
{

private:

    std::map<std::string, std::unique_ptr<Parser_CMD>> commands;



public:

    Parser_Command()
    {
        // Add commands to the map
        commands["help"] = std::make_unique<Command_Help>(commands);

        commands["exit"] = std::make_unique<Command_Exit>();

        commands["math"] = std::make_unique<Command_Switch_Math>();
    }

    // Execute the command with given name and arguments
    CMD_RESULT Execute(const std::string& cmd, const std::string& args)
    {
        CMD_RESULT _resoult = CMD_RESULT::INVALID;

        auto _foundCommand = commands.find(cmd);

        if (_foundCommand != commands.end())
        {
            _resoult = _foundCommand->second->Execute(args);
        }

        return _resoult;
    }

};