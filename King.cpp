#include "King.h"

King::King(Color color) : ChessPiece(color) {}

bool King::isValidMove(const QPoint &from, const QPoint &to, ChessBoard* board) const
{
    if(to==from) return false;

    if(abs(to.x()-from.x()) <=1 && abs(to.y()-from.y()) <= 1) return true;

    return false;

}
