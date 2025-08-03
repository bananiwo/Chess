#include "Bishop.h"

Bishop::Bishop(Color color) : ChessPiece(color) {}

bool Bishop::canMove(const QPoint &from, const QPoint &to) const
{
    if(to==from) return false;

    int diffX = to.x() - from.x();
    int diffY = to.y() - from.y();
    if(abs(diffX) != abs(diffY)) return false;

    /*int directionX = (to.x() > from.x()) ? 1 : -1;
    int directionY = (to.y() > from.y()) ? 1 : -1;
    int x = from.x() + directionX;
    int y = from.y() + directionY;
    while(x != to.x() && y != to.y())
    {
        if(board->getPieceAt(QPoint(x,y)))
            return false;

        x += directionX;
        y += directionY;
    }

    ChessPiece *piece = board->getPieceAt(to);
    if(piece && piece->getColor()==m_color) return false;*/

    return true;
}
