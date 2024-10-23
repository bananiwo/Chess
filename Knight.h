#pragma once

#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
    Knight(Color color);
    bool isValidMove(const QPoint &from, const QPoint &to, ChessBoard* board) const override;
};
