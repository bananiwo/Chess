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
    bool tryMovePiece(const QPoint& from, const QPoint& to) const;
    void movePiece(const QPoint& from, const QPoint& to);
    void restartBoard();

private:
    bool isDiagonalPathClear(const QPoint &from, const QPoint &to) const;
    bool isStraightPathClear(const QPoint &from, const QPoint &to) const;
    bool isDestinationValid(const QPoint &from, const QPoint &to) const;
    bool isPawnCaptureValid(const QPoint &from, const QPoint &to) const;
    void handlePromotion(const QPoint &pos);
    bool isGuardedByEnemy(ChessPiece::Color color, const QPoint &to) const;


private:
    QVector<QVector<ChessPiece*>> m_grid;
    bool m_isBoardReversed = false;
};
