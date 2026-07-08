#pragma once

#include "GameEngine.hpp"

class GameLoop {
public:
    static void step(GameEngine& engine, long long deltaMs);
};
