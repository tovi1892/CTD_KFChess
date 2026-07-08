#include "GameEngine.hpp"

#include "PathValidator.hpp"
#include "Board/MovementStrategyFactory.hpp"
#include "Systems/CollisionSystem.hpp"

#include <algorithm>
#include <cmath>

GameEngine::GameEngine()
    :
    currentTimeMs(0),
    selectedPos({-1,-1}),
    hasSelection(false),
    gameState(GameState::InProgress)
{
}

bool GameEngine::isGameOver() const noexcept
{
    return gameState == GameState::GameOver;
}

void GameEngine::endGame()
{
    if (gameState == GameState::GameOver)
    {
        return;
    }

    gameState = GameState::GameOver;
    hasSelection = false;
    selectedPos = {-1, -1};

    for (auto& move : activeMoves)
    {
        move.isActive = false;
    }
}

bool GameEngine::isKingToken(const std::string& token) const
{
    return token.size() >= 2 && token[1] == 'K';
}

bool GameEngine::isPromotionRow(char color, int row, size_t boardHeight) const
{
    if (boardHeight == 0)
    {
        return false;
    }

    return (color == 'w' && row == 0) || (color == 'b' && row == static_cast<int>(boardHeight) - 1);
}

std::string GameEngine::promotedToken(const std::string& token, int destRow, size_t boardHeight) const
{
    if (token.size() < 2 || token[1] != 'P')
    {
        return token;
    }

    if (!isPromotionRow(token[0], destRow, boardHeight))
    {
        return token;
    }

    return (token[0] == 'w') ? "wQ" : "bQ";
}

void GameEngine::initBoard(
    const Board& initialBoard)
{
    currentTimeMs = 0;
    selectedPos = {-1,-1};
    hasSelection = false;
    nextMoveOrder = 0;
    activeMoves.clear();
    gameState = GameState::InProgress;
    board = initialBoard;
}
long long GameEngine::calculateDurationMs(
    const std::string& token,
    Position src,
    Position dest)
{
    const auto strategy = MovementStrategyFactory::create(token);
    int distance = std::max(
        std::abs(dest.row - src.row),
        std::abs(dest.col - src.col));

    return distance * strategy->speedMsPerSquare();
}
bool GameEngine::isPieceMoving(Position pos) const
{
    for(const auto& move : activeMoves)
    {
        if(move.isActive &&
           move.src == pos)
        {
            return true;
        }
    }

    return false;
}
bool GameEngine::losesHeadOnCollision(
    const PendingMove& move) const
{
    for (const auto& other : activeMoves)
    {
        if (!other.isActive)
        {
            continue;
        }

        if (&other == &move)
        {
            continue;
        }

        if (hasMovementConflict(move, other))
        {
            return move.order > other.order;
        }
    }

    return false;
}

std::vector<Position> GameEngine::buildPath(Position src, Position dest) const
{
    std::vector<Position> path;

    if (src == dest)
    {
        return path;
    }

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
}

bool GameEngine::hasMovementConflict(
    const PendingMove& first,
    const PendingMove& second) const
{
    return CollisionSystem::hasMovementConflict(first, second);
}
void GameEngine::handleClick(int x, int y)
{
    if (gameState == GameState::GameOver)
    {
        return;
    }

    int col = x / 100;
    int row = y / 100;

    if (row < 0 || row >= static_cast<int>(board.getHeight()) ||
        col < 0 || col >= static_cast<int>(board.getWidth()))
    {
        return;
    }

    Board currentBoard = getRenderedBoard();

    std::string token =
        currentBoard.getTokenAt(row, col);

    if (!hasSelection)
    {
        if (token != "." &&
            !isPieceMoving({row, col}))
        {
            selectedPos = {row, col};
            hasSelection = true;
        }

        return;
    }

    std::string srcToken =
        currentBoard.getTokenAt(
            selectedPos.row,
            selectedPos.col);

    char srcColor = srcToken[0];
    char destColor = token[0];

    if (token != "." &&
        srcColor == destColor)
    {
        if (!isPieceMoving({row, col}))
        {
            selectedPos = {row, col};
        }

        return;
    }

    {
        const auto movementStrategy = MovementStrategyFactory::create(srcToken);
        if (!movementStrategy->isLegalMove(
                currentBoard,
                srcToken,
                selectedPos,
                {row, col}))
        {
            hasSelection = false;
            return;
        }
    }

    if (!PathValidator::isValidTarget(
            currentBoard,
            selectedPos.row,
            selectedPos.col,
            row,
            col))
    {
        hasSelection = false;
        return;
    }

    if (!PathValidator::isPathClear(
            currentBoard,
            selectedPos.row,
            selectedPos.col,
            row,
            col))
    {
        hasSelection = false;
        return;
    }

    PendingMove move;

    move.token = srcToken;
    move.src = selectedPos;
    move.dest = {row, col};
    move.startTimeMs = currentTimeMs;
    move.order = nextMoveOrder++;
    
    move.arrivalTimeMs =
    currentTimeMs +
    calculateDurationMs(
        srcToken,
        selectedPos,
        {row, col});

    move.isActive = true;

    activeMoves.push_back(move);

    board.setTokenAt(
        selectedPos.row,
        selectedPos.col,
        ".");

    hasSelection = false;
}
void GameEngine::advanceTime(long long ms)
{
    if (gameState == GameState::GameOver)
    {
        return;
    }

    currentTimeMs += ms;

    std::vector<PendingMove*> dueMoves;

    for (auto& move : activeMoves)
    {
        if (move.isActive && currentTimeMs >= move.arrivalTimeMs)
        {
            dueMoves.push_back(&move);
        }
    }

    std::stable_sort(
        dueMoves.begin(),
        dueMoves.end(),
        [](const PendingMove* left, const PendingMove* right)
        {
            return left->order < right->order;
        });

    for (auto* move : dueMoves)
    {
        if (!move->isActive)
        {
            continue;
        }

        bool shouldCancel = false;

        for (auto& other : activeMoves)
        {
            if (!other.isActive || &other == move)
            {
                continue;
            }

            if (hasMovementConflict(*move, other))
            {
                if (move->order > other.order)
                {
                    shouldCancel = true;
                    break;
                }

                if (move->order < other.order)
                {
                    other.isActive = false;
                }
            }
        }

        if (shouldCancel)
        {
            move->isActive = false;
            continue;
        }

        const std::string capturedToken =
            board.getTokenAt(move->dest.row, move->dest.col);

        const std::string promotedMoveToken =
            promotedToken(move->token, move->dest.row, board.getHeight());

        board.setTokenAt(
            move->dest.row,
            move->dest.col,
            promotedMoveToken);

        if (isKingToken(capturedToken))
        {
            endGame();
        }

        move->isActive = false;
    }
}
Board GameEngine::getRenderedBoard() const
{
    Board rendered = board;

    for (const auto& move : activeMoves)
    {
        if (!move.isActive)
        {
            continue;
        }

        if (currentTimeMs < move.arrivalTimeMs)
        {
            rendered.setTokenAt(
                move.src.row,
                move.src.col,
                move.token);
        }
        else
        {
            rendered.setTokenAt(
                move.dest.row,
                move.dest.col,
                move.token);
        }
    }

    return rendered;
}