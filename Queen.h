#pragma once

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
    Queen(Color color);
    bool canMove(const QPoint &from, const QPoint &to) const override;
};
