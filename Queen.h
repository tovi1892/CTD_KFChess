#pragma once
#include "piece.h"
#include <cstdlib>

class Queen : public Piece {
public:
    Queen(Color c) : Piece(c, 'Q') {}

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) const override {
        int dr = std::abs(toRow - fromRow);
        int dc = std::abs(toCol - fromCol);
        bool diagonal = dr == dc && dr > 0;
        bool straight = (fromRow == toRow) != (fromCol == toCol);
        return diagonal || straight;
    }
};
