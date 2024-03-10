#include "parser_Graph.h"



CMD_RESULT Parser_Graph::Execute(const std::string& args, CommandData_t& outCommandData)
{
    CMD_RESULT _return = CMD_RESULT::INPUT_INVALID;

    std::vector<std::string> _stringVector = StringCommandParser::Split_String(args);

    if (_stringVector.size() == parameters_Cnt)
    {
        try
        {
            outCommandData.vector_float = StringCommandParser::Get_FloatVector_FromStringVector(_stringVector, (size_t)(parameters_Cnt - 1));

            if (_stringVector.size() == parameters_Cnt)
            {
                outCommandData.vector_string = StringCommandParser::Get_StringVector_FromCommand(_stringVector, outCommandData.vector_float.size(), _stringVector.size());

                if (outCommandData.vector_string[0].length() == 1)
                    _return = CMD_RESULT::GL_DRAW_GRAPH;
            }
        }
        catch (const std::exception& e) {
            outCommandData.result = "ERROR: " + std::string(e.what()) + '\n';
        }
    }
    else {
        outCommandData.result = "ERROR: Invalid parameters\n";
    }

    return _return;
}