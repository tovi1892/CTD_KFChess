#pragma once

#include "Board.hpp"
#include <ostream>


class BoardRenderer {
public:
    static void print(
        std::ostream& output,
        const Board& board
    );
};