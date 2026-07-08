#pragma once

#include <memory>
#include <string>
#include "MovementStrategy.hpp"

class MovementStrategyFactory {
public:
    static std::unique_ptr<MovementStrategy> create(std::string_view token);
};
