#include "StringCommandParser.h"



std::vector<std::string> StringCommandParser::Get_StringVector_FromCommand(const std::vector<std::string>& stringVector, const size_t firstIdx, const size_t lastIdx)
{
    std::vector<std::string> _vector_s;

    _vector_s.reserve(lastIdx - firstIdx);

    for (size_t i = firstIdx; i < lastIdx; i++) {
        _vector_s.push_back(stringVector[i]);
    }

    return _vector_s;
}

std::vector<float> StringCommandParser::Get_FloatVector_FromStringVector(const std::vector<std::string>& stringVector, const size_t parametersCnt)
{
    std::vector<float> _vector_f;

    _vector_f.reserve(parametersCnt);

    for (size_t i = 0; i < parametersCnt; i++)
    {
        try
        {
            const float _floatValue = std::stof(stringVector[i]);
            _vector_f.push_back(_floatValue);
        }
        catch (const std::invalid_argument&) {
            std::cerr << "Invalid argument: " << stringVector[i] << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Out of range: " << e.what() << std::endl;
        }
    }

    return _vector_f;
}



std::vector<std::string> StringCommandParser::Split_String(const std::string& args)
{
    std::vector<std::string> _tokens;
    std::istringstream _ss(args);
    std::string _token;

    while (_ss >> _token) {
        _tokens.push_back(_token);
    }

    return _tokens;
}

std::string StringCommandParser::Remove_EmptySpaces(const std::string& expression)
{
    std::string exp;

    for (char c : expression)
    {
        if (c != ' ')
            exp += c;
    }

    return exp;
}