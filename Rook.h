#pragma once

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
    Rook(Color color);
    bool isValidMove(const QPoint& from, const QPoint& to, ChessBoard* board) const override;
};
