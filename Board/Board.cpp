#include "Board.hpp"

#include <cmath>
#include <unordered_set>

namespace {

bool isMovePatternForPiece(
    const std::string& pieceType,
    int srcRow,
    int srcCol,
    int destRow,
    int destCol,
    size_t boardHeight,
    bool allowDoubleStep)
{
    if (pieceType.size() < 2)
    {
        return false;
    }

    if (pieceType[1] == 'P')
    {
        char color = pieceType[0];
        int direction = (color == 'w') ? -1 : 1;
        int rowDelta = destRow - srcRow;
        int colDelta = std::abs(destCol - srcCol);

        if (colDelta == 0)
        {
            if (rowDelta == direction)
            {
                return true;
            }

            if (allowDoubleStep && rowDelta == 2 * direction)
            {
                // Starting row depends on board height and color.
                // In this project rows are indexed top-to-bottom (0..boardHeight-1).
                // White pawns start at the bottom row (boardHeight-1) and move upward (decreasing indices).
                // Black pawns start at the top row (0) and move downward (increasing indices).
                int initialRow = (color == 'w') ? static_cast<int>(boardHeight) - 1 : 0;
                return srcRow == initialRow;
            }

            return false;
        }

        return colDelta == 1 && rowDelta == direction;
    }

    char type = pieceType[1];
    int dRow = std::abs(destRow - srcRow);
    int dCol = std::abs(destCol - srcCol);

    switch (type)
    {
        case 'K':
            return dRow <= 1 && dCol <= 1;

        case 'R':
            return srcRow == destRow || srcCol == destCol;

        case 'B':
            return dRow == dCol;

        case 'Q':
            return srcRow == destRow || srcCol == destCol || dRow == dCol;

        case 'N':
            return (dRow == 2 && dCol == 1) || (dRow == 1 && dCol == 2);
    }

    return false;
}

} // namespace

void Board::clear()
{
    grid.clear();
}

void Board::addRow(const std::vector<std::string>& row)
{
    grid.push_back(row);
}

const std::vector<std::vector<std::string>>& Board::getGrid() const
{
    return grid;
}

bool Board::isEmpty() const
{
    return grid.empty();
}

size_t Board::getWidth() const
{
    return grid.empty() ? 0 : grid[0].size();
}

size_t Board::getHeight() const
{
    return grid.size();
}

std::string Board::getTokenAt(int r, int c) const
{
    return grid[r][c];
}

void Board::setTokenAt(int r, int c, const std::string& token)
{
    grid[r][c] = token;
}

bool Board::isValidToken(std::string_view token)
{
    static const std::unordered_set<std::string_view> validTokens = {
        ".",
        "wK", "wQ", "wR", "wB", "wN", "wP",
        "bK", "bQ", "bR", "bB", "bN", "bP"
    };

    return validTokens.find(token) != validTokens.end();
}

bool Board::isLegalMovePattern(
    const std::string& pieceType,
    int srcRow,
    int srcCol,
    int destRow,
    int destCol)
{
    if (srcRow == destRow && srcCol == destCol)
    {
        return false;
    }

    return isMovePatternForPiece(pieceType, srcRow, srcCol, destRow, destCol, 0, false);
}

bool Board::isLegalMovePattern(
    const std::string& pieceType,
    int srcRow,
    int srcCol,
    int destRow,
    int destCol,
    size_t boardHeight)
{
    if (srcRow == destRow && srcCol == destCol)
    {
        return false;
    }

    return isMovePatternForPiece(pieceType, srcRow, srcCol, destRow, destCol, boardHeight, true);
}
