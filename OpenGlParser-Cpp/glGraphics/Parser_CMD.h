#pragma once

#include <map>
#include <iostream>
#include <string>

#include "CMD.h"



class Parser_CMD
{
public:

    virtual ~Parser_CMD() {}



    virtual CMD_RESULT Execute(const std::string& args) = 0;

};
