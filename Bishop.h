#pragma once

#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(Color color);
    bool isValidMove(const QPoint &from, const QPoint &to, ChessBoard* board) const override;
};
