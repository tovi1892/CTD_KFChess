#pragma once
#include "piece.h"
#include <cstdlib>

class Rook : public Piece {
public:
    Rook(Color c) : Piece(c, 'R') {}

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) const override {
        return (fromRow == toRow) != (fromCol == toCol);
    }
};
