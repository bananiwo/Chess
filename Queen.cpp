#include "Queen.h"
#include <QDebug>

Queen::Queen(Color color) : ChessPiece(color) {}

bool Queen::isValidMove(const QPoint &from, const QPoint &to, ChessBoard* board) const
{
    if(to==from) return false;

    int diffX = to.x() - from.x();
    int diffY = to.y() - from.y();
    if((abs(diffX) != abs(diffY)) && (from.x() != to.x()) && (from.y() != to.y())) return false;
    if(from.x() == to.x())
    {
        int direction = (to.y() > from.y()) ? 1 : -1;
        for(int y=from.y()+direction; y!=to.y(); y+=direction)
        {
            if(board->getPieceAt(QPoint(from.x(), y))) return false;
        }
    }
    else if(from.y() == to.y())
    {
        int direction = (to.x() > from.x()) ? 1 : -1;
        for(int x=from.x()+direction; x!=to.x(); x+=direction)
        {
            if(board->getPieceAt(QPoint(x, from.y()))) return false;
        }
    }
    else
    {
        int directionX = (to.x() > from.x()) ? 1 : -1;
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
    }

    ChessPiece *piece = board->getPieceAt(to);
    if(piece && piece->getColor()==m_color) return false;

    return true;
}
