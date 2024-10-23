#include "Bishop.h"

Bishop::Bishop(Color color) : ChessPiece(color) {}

bool Bishop::isValidMove(const QPoint &from, const QPoint &to, ChessBoard* board) const
{
    if(to==from) return false;

    int diffX = to.x() - from.x();
    int diffY = to.y() - from.y();
    if(diffX == diffY || diffX == -diffY) return true;

    return false;
}
