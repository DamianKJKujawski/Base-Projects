#pragma once

#include "Parser_CMD.h"



class Parser_Graph : public Parser_CMD
{

    const int parameters_Cnt = 4;



public:

    CMD_RESULT Execute(const std::string& args, std::vector<float>& outputVector_f, std::vector<std::string>& outputVector_s) override
    {
        CMD_RESULT _return = CMD_RESULT::INVALID;

        std::vector<std::string> _stringVector = ArgParser::Split_String(args);

        if (_stringVector.size() == parameters_Cnt)
        {
            try
            {
                outputVector_f = ArgParser::Convert_StringVectorToFloatVector(_stringVector, (size_t)(parameters_Cnt - 1));

                if (_stringVector.size() == parameters_Cnt)
                {
                    outputVector_s = ArgParser::Get_StringArrayFromCommand(_stringVector, outputVector_f.size(), _stringVector.size());

                    if (outputVector_s[0].length() == 1)
                    {
                        _return = CMD_RESULT::GL_DRAW_GRAPH;
                    }
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }

        return _return;
    }
};
