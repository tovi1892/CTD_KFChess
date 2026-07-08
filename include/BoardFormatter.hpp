#pragma once

#include "Board.hpp"
#include <ostream>


class BoardFormatter {

public:

    static void print(
        std::ostream& output,
        const Board& board
    );

};