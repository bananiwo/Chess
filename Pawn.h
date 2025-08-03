#pragma once

#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
    Pawn(Color color);
    bool canMove(const QPoint &from, const QPoint &to) const override;
};
