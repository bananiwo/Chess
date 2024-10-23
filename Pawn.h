#pragma once

#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
    Pawn(Color color);
    bool isValidMove(const QPoint &from, const QPoint &to, ChessBoard* board) const override;
};
