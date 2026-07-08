#include "CollisionSystem.hpp"

bool CollisionSystem::hasMovementConflict(
    const PendingMove& first,
    const PendingMove& second
)
{
    if (!first.isActive || !second.isActive)
    {
        return false;
    }

    if (&first == &second)
    {
        return false;
    }

    if (first.src == second.src ||
        first.dest == second.dest ||
        first.src == second.dest ||
        first.dest == second.src)
    {
        return first.token[0] != second.token[0] ||
               first.src == second.dest ||
               first.dest == second.src;
    }

    auto buildPath = [](Position src, Position dest)
    {
        std::vector<Position> path;
        if (src == dest)
            return path;

        int rowStep = (dest.row > src.row) ? 1 : ((dest.row < src.row) ? -1 : 0);
        int colStep = (dest.col > src.col) ? 1 : ((dest.col < src.col) ? -1 : 0);
        Position current = src;
        path.push_back(current);

        while (current.row != dest.row || current.col != dest.col)
        {
            current.row += rowStep;
            current.col += colStep;
            path.push_back(current);
        }

        return path;
    };

    auto firstPath = buildPath(first.src, first.dest);
    auto secondPath = buildPath(second.src, second.dest);

    for (const auto& position : firstPath)
    {
        for (const auto& otherPosition : secondPath)
        {
            if (position == otherPosition)
            {
                return true;
            }
        }
    }

    return false;
}
