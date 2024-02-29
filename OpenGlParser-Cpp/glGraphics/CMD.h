#pragma once



enum class CMD_RESULT
{
    CORRECT,
    EMPTY,
    INVALID,

    SWITCH_TO_MATH_PARSER,
    SWITCH_TO_COMMAND_PARSER,

    EXIT,
};
