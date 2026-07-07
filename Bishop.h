#pragma once
#include "piece.h"
#include <cstdlib>

class Bishop : public Piece {
public:
    Bishop(Color c) : Piece(c, 'B') {}

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) const override {
        return std::abs(toRow - fromRow) == std::abs(toCol - fromCol) && (toRow != fromRow);
    }
};
