#pragma once

#include "ChessPiece.h"

class King : public ChessPiece
{
public:
    King(Color color);
    bool isValidMove(const QPoint &from, const QPoint &to, ChessBoard* board) const override;
};
