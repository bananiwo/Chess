#include "King.h"

King::King(Color color) : ChessPiece(color) {}

bool King::canMove(const QPoint &from, const QPoint &to) const
{
    if(to==from) return false;

    if(abs(to.x()-from.x()) > 1 || abs(to.y()-from.y()) > 1) return false;

    return true;
}
