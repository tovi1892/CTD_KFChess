#pragma once
#include "piece.h"
#include <cstdlib>

class Knight : public Piece {
public:
    Knight(Color c) : Piece(c, 'N') {}

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) const override {
        int dr = std::abs(toRow - fromRow);
        int dc = std::abs(toCol - fromCol);
        return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
    }
};
