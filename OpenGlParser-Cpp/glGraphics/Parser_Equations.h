#pragma once

#include <map>
#include <iostream>
#include <string>

#include "CMD.h"



class Parser_Equations
{
public:

    virtual ~Parser_Equations() {}



    virtual CMD_RESULT Parse(const std::string& expression, double& result) = 0;

};
