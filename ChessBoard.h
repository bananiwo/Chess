#pragma once

#include "ChessPiece.h"
#include <QVector>

class ChessPiece;

class ChessBoard
{
public:
    ChessBoard();
    void setupBoard();
    ChessPiece *getPieceAt(const QPoint& pos) const;
    bool movePiece(const QPoint& from, const QPoint& to);

private:
    QVector<QVector<ChessPiece*>> m_board;
};
