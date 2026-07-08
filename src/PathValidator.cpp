#include "PathValidator.hpp"



bool PathValidator::isValidTarget(
    const Board& board,
    int srcRow,
    int srcCol,
    int destRow,
    int destCol)
{
    std::string src =
        board.getTokenAt(srcRow,srcCol);


    std::string dest =
        board.getTokenAt(destRow,destCol);



    if(src[1]=='P')
    {
        if(dest==".")
        {
            if (!Board::isLegalMovePattern(
                    src,
                    srcRow,
                    srcCol,
                    destRow,
                    destCol,
                    board.getHeight()))
            {
                return false;
            }

            int rowDelta = destRow - srcRow;
            int direction = (src[0] == 'w') ? -1 : 1;

            if (rowDelta == 2 * direction)
            {
                int intermediateRow = srcRow + direction;
                return board.getTokenAt(intermediateRow, srcCol) == ".";
            }

            return true;
        }

        if(src[0]==dest[0] || srcCol==destCol)
            return false;

        return Board::isLegalMovePattern(
            src,
            srcRow,
            srcCol,
            destRow,
            destCol,
            board.getHeight());
    }

    if(dest==".")
    {
        return true;
    }

    if(src[0]==dest[0])
        return false;

    return true;
}




bool PathValidator::isPathClear(
    const Board& board,
    int srcRow,
    int srcCol,
    int destRow,
    int destCol)
{

    std::string piece =
        board.getTokenAt(srcRow,srcCol);


    if(piece[1]=='N')
        return true;



    int rowStep =
        (destRow-srcRow==0)
        ?0
        :(destRow-srcRow>0?1:-1);


    int colStep =
        (destCol-srcCol==0)
        ?0
        :(destCol-srcCol>0?1:-1);



    int r=srcRow+rowStep;
    int c=srcCol+colStep;



    while(r!=destRow || c!=destCol)
    {
        if(board.getTokenAt(r,c)!=".")
            return false;


        r+=rowStep;
        c+=colStep;
    }


    return true;
}