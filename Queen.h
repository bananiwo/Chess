#pragma once

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
    Queen(Color color);
    bool canMove(const QPoint &from, const QPoint &to) const override;
    PieceType type() const override {return PieceType::Queen;};
};
