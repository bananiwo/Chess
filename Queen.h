#pragma once

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
    Queen(Color color);
    bool isValidMove(const QPoint &from, const QPoint &to, ChessBoard* board) const override;
};
