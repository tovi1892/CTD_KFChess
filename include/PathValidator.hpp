#pragma once

#include "Board.hpp"


class PathValidator {

public:

    static bool isPathClear(
        const Board& board,
        int srcRow,
        int srcCol,
        int destRow,
        int destCol
    );


    static bool isValidTarget(
        const Board& board,
        int srcRow,
        int srcCol,
        int destRow,
        int destCol
    );

};