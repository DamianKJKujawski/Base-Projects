#pragma once

#include "CMD.h"
#include "Struct.h"

#include <map>
#include <iostream>
#include <string>



class Parser_Base
{

public:

    virtual ~Parser_Base() {}



    virtual std::string Get_Description() = 0;
    virtual CMD_RESULT Execute(const std::string& args, CommandData_t& outCommandData) = 0;
    
};