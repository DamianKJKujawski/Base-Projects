#pragma once

#include <map>
#include <iostream>
#include <string>

#include "CMD.h"



class Parser_Equations
{
public:

    virtual ~Parser_Equations() {}



    virtual CMD_RESULT Parse(const std::string& expression, double& result, std::vector<float>& outputVector_f, std::vector<std::string>& outputVector_s) = 0;

};
