#pragma once

#include "Parser_CMD.h"



class Command_Line : public Parser_CMD
{
private:

    const int parameters_Cnt = 5;



public:

    CMD_RESULT Execute(const std::string& args, std::vector<float>& outputVector_f, std::vector<std::string>& outputVector_s) override
    {
        CMD_RESULT _return = CMD_RESULT::INVALID;

        std::vector<std::string> _stringVector = ArgParser::Split_String(args);

        if (_stringVector.size() == parameters_Cnt)
        {
            try 
            {
                outputVector_f = ArgParser::Convert_StringVectorToFloatVector(_stringVector, parameters_Cnt);

                _return = CMD_RESULT::GL_DRAW_LINE;
            }
            catch (const std::exception& e) 
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }  
        }

        return _return;
    }
};