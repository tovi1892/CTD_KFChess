#include "MovementStrategy.hpp"

#include <cmath>

bool PawnMovementStrategy::isLegalMove(
    const Board& board,
    std::string_view token,
    Position src,
    Position dest
) const
{
    if (token.size() < 2 || token[1] != 'P')
    {
        return false;
    }

    char color = token[0];
    int direction = (color == 'w') ? -1 : 1;
    int rowDelta = dest.row - src.row;
    int colDelta = std::abs(dest.col - src.col);

    const bool isCapture = board.getTokenAt(dest.row, dest.col) != ".";

    if (colDelta == 0)
    {
        if (isCapture)
        {
            return false;
        }

        if (rowDelta == direction)
        {
            return true;
        }

        if (rowDelta == 2 * direction)
        {
            int initialRow = (color == 'w') ? static_cast<int>(board.getHeight()) - 1 : 0;
            return src.row == initialRow;
        }

        return false;
    }

    if (colDelta == 1 && rowDelta == direction)
    {
        return isCapture && board.getTokenAt(dest.row, dest.col)[0] != color;
    }

    return false;
}

long long PawnMovementStrategy::speedMsPerSquare() const noexcept
{
    return 1200;
}

bool KingMovementStrategy::isLegalMove(
    const Board&,
    std::string_view,
    Position src,
    Position dest
) const
{
    int dRow = std::abs(dest.row - src.row);
    int dCol = std::abs(dest.col - src.col);
    return dRow <= 1 && dCol <= 1 && !(dRow == 0 && dCol == 0);
}

long long KingMovementStrategy::speedMsPerSquare() const noexcept
{
    return 1200;
}

bool QueenMovementStrategy::isLegalMove(
    const Board&,
    std::string_view,
    Position src,
    Position dest
) const
{
    int dRow = std::abs(dest.row - src.row);
    int dCol = std::abs(dest.col - src.col);
    return (src.row == dest.row || src.col == dest.col || dRow == dCol) && !(dRow == 0 && dCol == 0);
}

long long QueenMovementStrategy::speedMsPerSquare() const noexcept
{
    return 800;
}

bool RookMovementStrategy::isLegalMove(
    const Board&,
    std::string_view,
    Position src,
    Position dest
) const
{
    return (src.row == dest.row || src.col == dest.col) && !(src.row == dest.row && src.col == dest.col);
}

long long RookMovementStrategy::speedMsPerSquare() const noexcept
{
    return 900;
}

bool BishopMovementStrategy::isLegalMove(
    const Board&,
    std::string_view,
    Position src,
    Position dest
) const
{
    int dRow = std::abs(dest.row - src.row);
    int dCol = std::abs(dest.col - src.col);
    return dRow == dCol && dRow != 0;
}

long long BishopMovementStrategy::speedMsPerSquare() const noexcept
{
    return 900;
}

bool KnightMovementStrategy::isLegalMove(
    const Board&,
    std::string_view,
    Position src,
    Position dest
) const
{
    int dRow = std::abs(dest.row - src.row);
    int dCol = std::abs(dest.col - src.col);
    return (dRow == 2 && dCol == 1) || (dRow == 1 && dCol == 2);
}

long long KnightMovementStrategy::speedMsPerSquare() const noexcept
{
    return 1000;
}

bool InvalidMovementStrategy::isLegalMove(
    const Board&,
    std::string_view,
    Position,
    Position
) const
{
    return false;
}

long long InvalidMovementStrategy::speedMsPerSquare() const noexcept
{
    return 0;
}
