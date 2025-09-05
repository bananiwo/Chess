#include "Queen.h"

Queen::Queen(Color color) : ChessPiece(color) {}

bool Queen::canMove(const QPoint &from, const QPoint &to) const
{
    if(to==from) return false;

    int diffX = to.x() - from.x();
    int diffY = to.y() - from.y();
    if((abs(diffX) != abs(diffY)) && (from.x() != to.x()) && (from.y() != to.y())) return false;
    return true;
}
