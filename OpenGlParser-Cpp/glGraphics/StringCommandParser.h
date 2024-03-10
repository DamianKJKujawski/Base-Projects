#pragma once

#include <sstream>
#include <vector>

#include <iostream>
#include <string>



class StringCommandParser
{

public:

        static std::vector<std::string> Get_StringVector_FromCommand(const std::vector<std::string>& stringVector, const size_t firstIdx, const size_t lastIdx);
        static std::vector<float> Get_FloatVector_FromStringVector(const std::vector<std::string>& stringVector, const size_t parametersCnt);
        
        static std::vector<std::string> Split_String(const std::string& args);
        static std::string Remove_EmptySpaces(const std::string& expression);
};