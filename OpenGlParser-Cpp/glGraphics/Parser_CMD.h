#pragma once

#include <map>
#include <iostream>
#include <string>

#include <sstream>
#include <vector>

#include "CMD.h"



class ArgParser
{
public:

    static std::vector<std::string> Get_StringArrayFromCommand(const std::vector<std::string>& stringVector, int first_idx, int last_idx)
    {
        std::vector<std::string> _vector_s;

        _vector_s.reserve(last_idx - first_idx);

        for (int i = first_idx; i < last_idx; i++)
        {
            _vector_s.push_back(stringVector[i]);
        }

        return _vector_s;
    }

    static std::vector<float> Convert_StringVectorToFloatVector(const std::vector<std::string>& stringVector, size_t parametersCnt) 
    {
        std::vector<float> _vector_f;

        _vector_f.reserve(parametersCnt);

        for (int i=0; i< parametersCnt; i++)
        {
            try 
            {
                const float _floatValue = std::stof(stringVector[i]);
                _vector_f.push_back(_floatValue);
            }
            catch (const std::invalid_argument&) 
            {
                std::cerr << "Invalid argument: " << stringVector[i] << std::endl;
            }
            catch (const std::out_of_range& e) 
            {
                std::cerr << "Out of range: " << e.what() << std::endl;
            }
        }

        return _vector_f;
    }

    static std::vector<std::string> Split_String(const std::string& args)
    {
        std::vector<std::string> _tokens;
        std::istringstream _ss(args);
        std::string _token;

        while (_ss >> _token)
        {
            _tokens.push_back(_token);
        }

        return _tokens;
    }

};





class Parser_CMD
{
public:

    virtual ~Parser_CMD() {}



    virtual CMD_RESULT Execute(const std::string& args, std::vector<float>& outputVector, std::vector<std::string>& outputVector_s) = 0;

};
