#include "Rook.h"

Rook::Rook(Color color) : ChessPiece(color) {}

bool Rook::isValidMove(const QPoint& from, const QPoint& to, ChessBoard* board) const
{
    if(to==from) return false;
    if(from.x() != to.x() && from.y() != to.y()) return false;

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

    ChessPiece *piece = board->getPieceAt(to);
    if(piece && piece->getColor()==m_color) return false;


    return true;
}
