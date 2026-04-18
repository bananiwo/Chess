#pragma once

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
    Rook(Color color);
    bool canMove(const QPoint& from, const QPoint& to) const override;
    PieceType type() const override {return PieceType::Rook;};
};
