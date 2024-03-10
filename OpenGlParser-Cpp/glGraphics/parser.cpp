#include "parser.h"



#pragma region PRIVATE:

    CMD_RESULT Parser::Parse_Command(CommandData_t& outCommandData)
    {
        // Read Input text:
        std::string _input;
        std::cout << "CMD > ";
        std::getline(std::cin, _input);

        // Split Input text to Command and Arguments:
        size_t _spacePos = _input.find(' ');
        std::string _cmd = _input.substr(0, _spacePos);
        std::string _args = (_spacePos == std::string::npos) ? "" : _input.substr(_spacePos + 1);

        // Execute Command:
        return parser_Command.Execute(_cmd, _args, outCommandData);
    }

    CMD_RESULT Parser::Parse_MathExpression(CommandData_t& outCommandData)
    {
        // Read input text:
        std::string _input;
        std::cout << "MATH > ";
        std::getline(std::cin, _input);

        // Parse Math Expression:
        return parser_Math.Parse(_input, outCommandData);
    }

#pragma endregion



#pragma region PUBLIC:

    CMD_RESULT Parser::Parse_CMD(CommandData_t& outCommandData)
    {
        outCommandData.result.clear();

        // Get result:
        CMD_RESULT _CMD_Result = (this->*methodPtr)(outCommandData);

        return _CMD_Result;
    }

    void Parser::Execute_CMD(CMD_RESULT cmd, CommandData_t& outCommandData)
    {
        switch (cmd)
        {
        // SWITCH-es:
        case CMD_RESULT::CMD_SWITCH_TO_MATH_PARSER:
            this->methodPtr = &Parser::Parse_MathExpression;
            break;

        case CMD_RESULT::CMD_SWITCH_TO_COMMAND_PARSER:
            this->methodPtr = &Parser::Parse_Command;
            break;

        // MATH Parser:
        case CMD_RESULT::GL_DRAW_GRAPH:
            parser_Math.Reparse_LastExpression(outCommandData.vector_string[0][0], outCommandData);
            break;

        case CMD_RESULT::CMD_CLEAR_VARIABLES:
            parser_Math.Clear_UsedVariables();
            break;

        default:
            break;
        }
    }



    void Parser::DisplayResult(CommandData_t& outCommandData)
    {
        std::cout << outCommandData.result;
    
    }

#pragma endregion