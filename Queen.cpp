#include "Queen.h"

Queen::Queen(Color color) : ChessPiece(color) {}

bool Queen::isValidMove(const QPoint &from, const QPoint &to, ChessBoard* board) const
{
    if(to==from) return false;

    if(from.x() == to.x()) return true;
    if(from.y() == to.y()) return true;
    int diffX = to.x() - from.x();
    int diffY = to.y() - from.y();
    if(diffX == diffY || diffX == -diffY) return true;

    return false;
}
