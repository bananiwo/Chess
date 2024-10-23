#include "Knight.h"

Knight::Knight(Color color) : ChessPiece(color) {}

bool Knight::isValidMove(const QPoint &from, const QPoint &to, ChessBoard* board) const
{
    if(to==from) return false;

    if(((abs(to.x()-from.x()))==2 && abs(to.y()-from.y())==1) ||
            (abs(to.x()-from.x())==1 && abs(to.y()-from.y())==2))
        return true;

    return false;

}
