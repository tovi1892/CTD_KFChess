#pragma once

#include <string>
#include "Position.hpp"

struct PendingMove {
    std::string token;
    Position src;
    Position dest;
    long long arrivalTimeMs;
    long long startTimeMs;
    int order = 0;
    bool isActive = false;
};