#pragma once

#include "parser_Math.h"
#include "parser_Command.h"



class ParsersManager
{

private:

    CMD_RESULT(ParsersManager::* functionPtr)();

    // CMD Thread:
    Parser_Command _parser_Command;
    Parser_Math _parser_Math;



    CMD_RESULT Parse_Command()
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
        return _parser_Command.Execute(cmd, args);
    }

    CMD_RESULT Parse_Math()
    {
        std::string _input;
        std::cout << "MATH > ";
        std::getline(std::cin, _input);

        double _result = 0.0;

        // Parse Math Expression:
        return _parser_Math.Parse(_input, _result);
    }



public:

    ParsersManager() 
    {
        this->functionPtr = &ParsersManager::Parse_Command;
    }

    ~ParsersManager()
    {}



    CMD_RESULT Execute()
    {
        CMD_RESULT _CMD_Result = (this->*functionPtr)();

        switch (_CMD_Result)
        {
            case CMD_RESULT::SWITCH_TO_MATH_PARSER:
                this->functionPtr = &ParsersManager::Parse_Math;
                break;

            default:
                break;
        }

        return _CMD_Result;
    }

};

