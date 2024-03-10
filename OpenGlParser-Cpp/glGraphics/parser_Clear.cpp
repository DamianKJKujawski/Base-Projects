#include "parser_Clear.h"



CMD_RESULT Parser_Clear::Execute(const std::string& args, CommandData_t& outCommandData)
{
    outCommandData.result = "Variables cleared\n";

    return CMD_RESULT::CMD_CLEAR_VARIABLES;
}
