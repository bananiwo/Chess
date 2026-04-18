#include "Pawn.h"

Pawn::Pawn(Color color) : ChessPiece(color) {}

bool Pawn::canMove(const QPoint &from, const QPoint &to) const
{
    if(to==from) return false;

    // normal one-square move
    int direction = m_color == ChessPiece::White ? 1 : -1;
    if((to.x() == from.x()) &&
        to.y() == from.y()+direction)
    {
        return true;
    }

    // two-square move in first move
    if(!m_hasMoved &&
        to.x() == from.x() &&
        to.y() == from.y() + 2*direction)
    {
        return true;
    }

    // regular diagonal capture
    if(to.y() == from.y()+direction && abs(to.x()-from.x())==1)
    {
        return true;
    }

    return false;
}
