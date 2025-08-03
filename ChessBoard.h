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
    bool tryMovePiece(const QPoint& from, const QPoint& to);
    void movePiece(const QPoint& from, const QPoint& to);

private:
    bool isDiagonalPathClear(const QPoint &from, const QPoint &to) const;
    bool isStraightPathClear(const QPoint &from, const QPoint &to) const;
    bool isDestinationValid(const QPoint &from, const QPoint &to) const;
    bool isPawnCaptureValid(const QPoint &from, const QPoint &to) const;
    void handlePromotion(const QPoint &pos);

private:
    QVector<QVector<ChessPiece*>> m_grid;
};
