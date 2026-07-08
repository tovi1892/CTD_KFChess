#pragma once

#include <string>
#include "Board.hpp"
#include "Entities/Position.hpp"

class MovementStrategy {
public:
    virtual ~MovementStrategy() = default;

    virtual bool isLegalMove(
        const Board& board,
        std::string_view token,
        Position src,
        Position dest
    ) const = 0;

    virtual long long speedMsPerSquare() const noexcept = 0;
};

class PawnMovementStrategy : public MovementStrategy {
public:
    bool isLegalMove(
        const Board& board,
        std::string_view token,
        Position src,
        Position dest
    ) const override;

    long long speedMsPerSquare() const noexcept override;
};

class KingMovementStrategy : public MovementStrategy {
public:
    bool isLegalMove(
        const Board&,
        std::string_view token,
        Position src,
        Position dest
    ) const override;

    long long speedMsPerSquare() const noexcept override;
};

class QueenMovementStrategy : public MovementStrategy {
public:
    bool isLegalMove(
        const Board&,
        std::string_view token,
        Position src,
        Position dest
    ) const override;

    long long speedMsPerSquare() const noexcept override;
};

class RookMovementStrategy : public MovementStrategy {
public:
    bool isLegalMove(
        const Board&,
        std::string_view token,
        Position src,
        Position dest
    ) const override;

    long long speedMsPerSquare() const noexcept override;
};

class BishopMovementStrategy : public MovementStrategy {
public:
    bool isLegalMove(
        const Board&,
        std::string_view token,
        Position src,
        Position dest
    ) const override;

    long long speedMsPerSquare() const noexcept override;
};

class KnightMovementStrategy : public MovementStrategy {
public:
    bool isLegalMove(
        const Board&,
        std::string_view token,
        Position src,
        Position dest
    ) const override;

    long long speedMsPerSquare() const noexcept override;
};

class InvalidMovementStrategy : public MovementStrategy {
public:
    bool isLegalMove(
        const Board&,
        std::string_view,
        Position,
        Position
    ) const override;

    long long speedMsPerSquare() const noexcept override;
};
