#pragma once

#include "ChessBoard.h"
#include "PieceInfo.h"
#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>

class ChessBoardGUI : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoardGUI(QWidget *parent = nullptr);

public slots:
    void setupChessBoard();

private slots:
    void handleSquareClicked();

signals:
    void cellClicked(int row, int col);

public:
    void setPieceAt(QPoint pos, const PieceData& data);
    void highlightSquareBlueBorder(QPoint position);
    void highlightSquareRedBorder(QPoint position);
    void drawAllSquares();
    void swapSides();

private:
    QGridLayout *m_gridLayout;
    QVector<QVector<QPushButton*>> m_boardSquares;
    QPoint m_selectedPosition;
    bool m_isBoardReversed = false;
    QIcon m_whitePawn;
    QIcon m_whiteRook;
    QIcon m_whiteBishop;
    QIcon m_whiteKnight;
    QIcon m_whiteQueen;
    QIcon m_whiteKing;
    QIcon m_blackPawn;
    QIcon m_blackRook;
    QIcon m_blackBishop;
    QIcon m_blackKnight;
    QIcon m_blackQueen;
    QIcon m_blackKing;


    QPoint mirrorPointIfNeeded(QPoint point);
    void loadIcons();
};
