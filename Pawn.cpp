#include "Pawn.h"

Pawn::Pawn(Color color) : ChessPiece(color) {}

bool Pawn::isValidMove(const QPoint &from, const QPoint &to, ChessBoard* board) const
{
    if(to==from) return false;

    int direction = m_color == ChessPiece::White ? 1 : -1;
    if((to.x() != from.x()) ||
        to.y() != from.y()+direction) return false;

    ChessPiece *piece = board->getPieceAt(to);
    if(piece && piece->getColor() == m_color) return false;

    return true;

}
