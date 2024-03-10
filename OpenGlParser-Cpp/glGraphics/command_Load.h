#pragma once

#include "Parser_Base.h"



class Command_Load : public Parser_Base
{

private:

    const size_t parameters_Cnt = 1;



public:

    Command_Load() {}
    ~Command_Load() {}



    std::string Get_Description() override {
        return "Load Texture [Index Path]";
    }

    CMD_RESULT Execute(const std::string& args, CommandData_t& outCommandData) override;

};