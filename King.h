#pragma once

#include "ChessPiece.h"

class King : public ChessPiece
{
public:
    King(Color color);
    bool canMove(const QPoint &from, const QPoint &to) const override;
};
