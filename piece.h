#pragma once
#include <string>

enum class Color { White, Black };

class Piece {
public:
    Color color;
    char type; // K, R, B, Q, N, P

    Piece(Color c, char t) : color(c), type(t) {}
    virtual ~Piece() = default;

    virtual bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) const = 0;

    std::string toString() const {
        std::string s;
        s += (color == Color::White ? 'w' : 'b');
        s += type;
        return s;
    }
};
