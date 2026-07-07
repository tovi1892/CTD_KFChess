#pragma once
#include "piece.h"
#include <cstdlib>

class King : public Piece {
public:
    King(Color c) : Piece(c, 'K') {}

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) const override {
        int dr = std::abs(toRow - fromRow);
        int dc = std::abs(toCol - fromCol);
        return dr <= 1 && dc <= 1 && (dr + dc > 0);
    }
};
