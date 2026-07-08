#pragma once

#include "Board.hpp"
#include "PendingMove.hpp"
#include <vector>


class GameEngine {

private:

    enum class GameState {
        InProgress,
        GameOver
    };

    Board board;

    long long currentTimeMs;

    Position selectedPos;

    bool hasSelection;

    int nextMoveOrder = 0;

    GameState gameState = GameState::InProgress;

    std::vector<PendingMove> activeMoves;

    bool losesHeadOnCollision(const PendingMove& move) const;

    void endGame();

    bool isKingToken(const std::string& token) const;

    bool isPromotionRow(char color, int row, size_t boardHeight) const;

    std::string promotedToken(const std::string& token, int destRow, size_t boardHeight) const;

    bool hasMovementConflict(
        const PendingMove& first,
        const PendingMove& second
    ) const;

    std::vector<Position> buildPath(Position src, Position dest) const;

    long long calculateDurationMs(
        const std::string& token,
        Position src,
        Position dest
    );


    bool isPieceMoving(Position pos) const;


public:

    GameEngine();

    bool isGameOver() const noexcept;

    void initBoard(const Board& initialBoard);


    void handleClick(int x,int y);


    void advanceTime(long long ms);


    Board getRenderedBoard() const;

};