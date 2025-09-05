#pragma once

#include "PieceInfo.h"
#include "ChessSquareItem.h"
#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>

class ChessBoardGUI : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoardGUI(QWidget *parent = nullptr);

public slots:
    void setupChessBoard();

private slots:
    void handleSquareClicked(int row, int col);

signals:
    void cellClicked(int row, int col);

public:
    void setPieceAt(QPoint pos, const PieceData& data);
    void highlightSquareBlueBorder(QPoint position);
    void highlightSquareRedBorder(QPoint position);
    void clearHighlights();
    void swapSides();

private:
    QGraphicsScene *m_scene;
    QGraphicsView *m_graphicsView;
    QVector<QVector<ChessSquareItem*>> m_boardSquares;
    QGraphicsPixmapItem *m_pieceItems[8][8];
    QGraphicsTextItem *m_horizontalLabels[8];
    QGraphicsTextItem *m_verticalLabels[8];
    QPoint m_selectedPosition;
    bool m_isBoardReversed = false;
    QIcon m_whitePawn, m_whiteRook, m_whiteBishop, m_whiteKnight, m_whiteQueen, m_whiteKing;
    QIcon m_blackPawn, m_blackRook, m_blackBishop, m_blackKnight, m_blackQueen, m_blackKing;

    QPoint mirrorPointIfNeeded(QPoint point);
    void setLabels();
    void loadIcons();
};
