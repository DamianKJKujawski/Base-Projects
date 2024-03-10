#include "parser_Switch_Command.h"



CMD_RESULT Parser_Switch_Command::Execute(const std::string& args, CommandData_t& outCommandData)
{
    outCommandData.result = "CMD Parser: " + args + "\n";

    return CMD_RESULT::CMD_SWITCH_TO_COMMAND_PARSER;
}