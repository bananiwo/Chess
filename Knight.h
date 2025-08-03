#pragma once

#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
    Knight(Color color);
    bool canMove(const QPoint &from, const QPoint &to) const override;
};
