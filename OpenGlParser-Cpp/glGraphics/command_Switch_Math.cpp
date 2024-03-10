#include "command_Switch_Math.h"



CMD_RESULT Command_Switch_Math::Execute(const std::string& args, CommandData_t& outCommandData)
{
    outCommandData.result = "MATH Parser: " + args + "\n";

    return CMD_RESULT::CMD_SWITCH_TO_MATH_PARSER;
}