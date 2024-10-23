#include "Pawn.h"

Pawn::Pawn(Color color) : ChessPiece(color) {}

bool Pawn::isValidMove(const QPoint &from, const QPoint &to, ChessBoard* board) const
{
    if(to==from) return false;

    // normal one-square move
    int direction = m_color == ChessPiece::White ? 1 : -1;
    if((to.x() == from.x()) &&
        to.y() == from.y()+direction &&
        !board->getPieceAt(to))
    {
        return true;
    }

    // two-square move in first move
    if(!m_hasMoved &&
        to.x() == from.x() &&
        to.y() == from.y() + 2*direction &&
        !board->getPieceAt(QPoint(to.x(), from.y()+direction)) &&
        !board->getPieceAt(QPoint(to)))
    {
        return true;
    }

    // regular diagonal capture
    if(to.y() == from.y()+direction && abs(to.x()-from.x())==1)
    {
        ChessPiece *piece = board->getPieceAt(to);
        if(piece && piece->getColor() != m_color)
        {
            return true;
        }
    }

    return false;
}
