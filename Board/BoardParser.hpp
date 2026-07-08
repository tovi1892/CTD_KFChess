#pragma once

#include "Board.hpp"
#include <istream>


enum class ParseResult
{
    Success,
    UnknownToken,
    RowWidthMismatch
};



class BoardParser {

public:

    static ParseResult parse(
        std::istream& input,
        Board& outBoard
    );

};