#include "MovementStrategyFactory.hpp"
#include "MovementStrategy.hpp"

#include <memory>

std::unique_ptr<MovementStrategy> MovementStrategyFactory::create(std::string_view token)
{
    if (token.size() < 2)
    {
        return std::make_unique<InvalidMovementStrategy>();
    }

    switch (token[1])
    {
        case 'P':
            return std::make_unique<PawnMovementStrategy>();
        case 'K':
            return std::make_unique<KingMovementStrategy>();
        case 'Q':
            return std::make_unique<QueenMovementStrategy>();
        case 'R':
            return std::make_unique<RookMovementStrategy>();
        case 'B':
            return std::make_unique<BishopMovementStrategy>();
        case 'N':
            return std::make_unique<KnightMovementStrategy>();
        default:
            return std::make_unique<InvalidMovementStrategy>();
    }
}
