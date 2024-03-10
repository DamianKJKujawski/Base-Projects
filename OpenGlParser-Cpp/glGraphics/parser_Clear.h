#pragma once

#include "Parser_Base.h"



class Parser_Clear : public Parser_Base
{

public:

    Parser_Clear() {}
    ~Parser_Clear() {}



    std::string Get_Description() override {
        return "Clear variables";
    }

    CMD_RESULT Execute(const std::string& args, CommandData_t& outCommandData) override;

};
