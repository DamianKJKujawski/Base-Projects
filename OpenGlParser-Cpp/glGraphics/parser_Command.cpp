#include "parser_Command.h"



// Execute the command with given name and arguments
CMD_RESULT Parser_Command::Execute(const std::string& cmd, const std::string& args, CommandData_t& outCommandData)
{
    CMD_RESULT _resoult = CMD_RESULT::INPUT_INVALID;

    auto _foundCommand = commands.find(cmd);

    if (_foundCommand != commands.end())
    {
        _resoult = _foundCommand->second->Execute(args, outCommandData);
    }

    return _resoult;
}

