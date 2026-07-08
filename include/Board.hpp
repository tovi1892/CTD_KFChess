#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <unordered_set>


class Board {

private:

    std::vector<std::vector<std::string>> grid;


public:

    Board() = default;


    void clear();

    void addRow(const std::vector<std::string>& row);


    const std::vector<std::vector<std::string>>& getGrid() const;

    bool isEmpty() const;

    size_t getWidth() const;

    size_t getHeight() const;


    std::string getTokenAt(int r,int c) const;

    void setTokenAt(int r,int c,const std::string& token);


    static bool isValidToken(std::string_view token);


    static bool isLegalMovePattern(
        const std::string& pieceType,
        int srcRow,
        int srcCol,
        int destRow,
        int destCol
    );

    static bool isLegalMovePattern(
        const std::string& pieceType,
        int srcRow,
        int srcCol,
        int destRow,
        int destCol,
        size_t boardHeight
    );

};