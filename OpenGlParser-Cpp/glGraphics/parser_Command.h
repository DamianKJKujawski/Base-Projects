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
#include "command_Remove.h"

#include <map>



class Parser_Command
{

private:

    std::map<std::string, std::unique_ptr<Parser_Base>> commands;



public:

    Parser_Command()
    {
        commands["point"] = std::make_unique<Command_Point>();
        commands["line"] = std::make_unique<Command_Line>();
        commands["square"] = std::make_unique<Command_Square>();
        commands["text"] = std::make_unique<Command_Text>();

        commands["load"] = std::make_unique<Command_Load>();
        commands["texture"] = std::make_unique<Command_Texture>();

        commands["remove"] = std::make_unique<Command_Remove>();

        commands["help"] = std::make_unique<Command_Help>(commands);
        commands["math"] = std::make_unique<Command_Switch_Math>();
        commands["exit"] = std::make_unique<Command_Exit>();
    }



    CMD_RESULT Execute(const std::string& cmd, const std::string& args, CommandData_t& outCommandData);

};