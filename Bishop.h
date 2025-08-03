#pragma once

#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(Color color);
    bool canMove(const QPoint &from, const QPoint &to) const override;
};
