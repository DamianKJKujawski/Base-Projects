#pragma once

#include "Parser_CMD.h"



class Command_Load : public Parser_CMD
{
private:

    const int parameters_Cnt = 1;



public:

    CMD_RESULT Execute(const std::string& args, std::vector<float>& outputVector_f, std::vector<std::string>& outputVector_s) override
    {
        size_t _spacePos = args.find(' ');

        if(_spacePos == -1)
            return CMD_RESULT::INVALID;

        std::string _arg = args.substr(0, _spacePos);
        std::string _path = (_spacePos == std::string::npos) ? "" : args.substr(_spacePos + 1);

        std::vector<std::string> _vector_f;
        _vector_f.reserve(parameters_Cnt);
        _vector_f.push_back(_arg);

        outputVector_s.clear();
        outputVector_s.reserve(parameters_Cnt);
        outputVector_s.push_back(_path);

        outputVector_f.clear();
        outputVector_f = ArgParser::Convert_StringVectorToFloatVector(_vector_f, parameters_Cnt);

        return CMD_RESULT::GL_LOAD_TEXTURE;
    }
};