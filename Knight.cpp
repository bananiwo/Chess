#include "Knight.h"

Knight::Knight(Color color) : ChessPiece(color) {}

bool Knight::canMove(const QPoint &from, const QPoint &to) const
{
    if(to==from) return false;

    if(((abs(to.x()-from.x()))==2 && abs(to.y()-from.y())==1) ||
            (abs(to.x()-from.x())==1 && abs(to.y()-from.y())==2))
        return true;

    return false;

}
