#include "command_Remove.h"



CMD_RESULT Command_Remove::Execute(const std::string& args, CommandData_t& outCommandData)
{
    CMD_RESULT _return = CMD_RESULT::INPUT_INVALID;

    std::vector<std::string> _stringVector = StringCommandParser::Split_String(args);

    if (_stringVector.size() == parameters_Cnt)
    {
        try
        {
            outCommandData.vector_float = StringCommandParser::Get_FloatVector_FromStringVector(_stringVector, parameters_Cnt);

            _return = CMD_RESULT::CMD_REMOVE;
        }
        catch (const std::exception& e)
        {
            outCommandData.result = "ERROR: " + std::string(e.what()) + '\n';
        }
    }
    else {
        outCommandData.result = "ERROR: Invalid parameters\n";
    }

    return _return;
}