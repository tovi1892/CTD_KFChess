#include "GameLoop.hpp"

void GameLoop::step(GameEngine& engine, long long deltaMs)
{
    engine.advanceTime(deltaMs);
}
