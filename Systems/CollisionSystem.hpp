#pragma once

#include <vector>
#include "Entities/PendingMove.hpp"

class CollisionSystem {
public:
    static bool hasMovementConflict(
        const PendingMove& first,
        const PendingMove& second
    );
};
