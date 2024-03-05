#pragma once

#include "parser_Math.h"
#include "parser_Command.h"



class ParsersManager
{

private:

    CMD_RESULT(ParsersManager::* methodPtr)(std::vector<float>& outputVector, std::vector<std::string>& outputVector_s);

    // CMD Thread:
    Parser_Command _parser_Command;
    Parser_Math _parser_Math;



    CMD_RESULT Parse_Command(std::vector<float>& outputVector_f, std::vector<std::string>& outputVector_s)
    {
        // Read input text:
        std::string _input;
        std::cout << "CMD > ";
        std::getline(std::cin, _input);

        // Split input text to command and arguments:
        size_t spacePos = _input.find(' ');
        std::string cmd = _input.substr(0, spacePos);
        std::string args = (spacePos == std::string::npos) ? "" : _input.substr(spacePos + 1);

        // Execute Command:
        return _parser_Command.Execute(cmd, args, outputVector_f, outputVector_s);
    }

    CMD_RESULT Parse_Math(std::vector<float>& outputVector_f, std::vector<std::string>& outputVector_s)
    {
        CMD_RESULT _return = CMD_RESULT::INVALID;

        std::string _input;
        std::cout << "MATH > ";
        std::getline(std::cin, _input);

        double _result = 0.0;

        // Parse Math Expression:
        _return = _parser_Math.Parse(_input, _result, outputVector_f, outputVector_s);

        if(_return == CMD_RESULT::CORRECT)
            std::cout << _result << std::endl;

        return _return;
    }



public:

    ParsersManager() 
    {
        this->methodPtr = &ParsersManager::Parse_Command;
    }

    ~ParsersManager()
    {}



    CMD_RESULT Execute(std::vector<float>& outputVector_f, std::vector<std::string>& outputVector_s)
    {
        CMD_RESULT _CMD_Result = (this->*methodPtr)(outputVector_f, outputVector_s);

        switch (_CMD_Result)
        {
            case CMD_RESULT::CMD_SWITCH_TO_MATH_PARSER:
                this->methodPtr = &ParsersManager::Parse_Math;
                break;

            case CMD_RESULT::CMD_SWITCH_TO_COMMAND_PARSER:
                this->methodPtr = &ParsersManager::Parse_Command;
                break;

            case CMD_RESULT::GL_DRAW_GRAPH:
            {
                double _result;
                for (float currentValue = 0; currentValue < 10; currentValue+=0.1f)
                {
                    _parser_Math.Recalculate(outputVector_s[0][0], currentValue, _result);
                    outputVector_f.push_back(_result);
                }
            }
            break;

            default:
                break;
        }

        return _CMD_Result;
    }

};

