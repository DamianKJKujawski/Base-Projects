#include "command_Load.h"
#include "StringCommandParser.h"



CMD_RESULT Command_Load::Execute(const std::string& args, CommandData_t& outCommandData)
{
    CMD_RESULT _return = CMD_RESULT::INPUT_INVALID;

    size_t _spacePos = args.find(' ');

    if (_spacePos == -1)
    {
        _return = CMD_RESULT::INPUT_INVALID;
    }
    else
    {
        std::string _arg = args.substr(0, _spacePos);
        std::string _path = (_spacePos == std::string::npos) ? "" : args.substr(_spacePos + 1);

        std::vector<std::string> _vector_f;
        _vector_f.reserve(parameters_Cnt);
        _vector_f.push_back(_arg);

        outCommandData.vector_string.clear();
        outCommandData.vector_string.reserve(parameters_Cnt);
        outCommandData.vector_string.push_back(_path);

        outCommandData.vector_float.clear();
        outCommandData.vector_float = StringCommandParser::Get_FloatVector_FromStringVector(_vector_f, parameters_Cnt);

        _return = CMD_RESULT::GL_LOAD_TEXTURE;
    }

    return _return;
}