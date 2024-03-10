#include "command_Text.h"



CMD_RESULT Command_Text::Execute(const std::string& args, CommandData_t& outCommandData)
{
    CMD_RESULT _return = CMD_RESULT::INPUT_INVALID;

    std::vector<std::string> _stringVector = StringCommandParser::Split_String(args);

    if (_stringVector.size() > parameters_Cnt)
    {
        try
        {
            outCommandData.vector_float = StringCommandParser::Get_FloatVector_FromStringVector(_stringVector, parameters_Cnt);

            if (outCommandData.vector_float.size() == parameters_Cnt)
            {
                outCommandData.vector_string = StringCommandParser::Get_StringVector_FromCommand(_stringVector, parameters_Cnt, _stringVector.size());
            }

            _return = CMD_RESULT::GL_DRAW_TEXT;
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