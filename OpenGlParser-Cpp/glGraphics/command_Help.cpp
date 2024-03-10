#include "command_Help.h"



CMD_RESULT Command_Help::Execute(const std::string& args, CommandData_t& outCommandData)
{
    outCommandData.result = "HELP: Available commands: " + args + "\n";

    for (const auto& command : commands)
    {
        outCommandData.result += "- " + command.first + " - ";
        outCommandData.result += command.second->Get_Description() + '\n';
    }

    return CMD_RESULT::CMD_HELP;
}