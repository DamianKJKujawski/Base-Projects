#include "command_Exit.h"



CMD_RESULT Command_Exit::Execute(const std::string& args, CommandData_t& outCommandData)
{
    return CMD_RESULT::EXIT;
}