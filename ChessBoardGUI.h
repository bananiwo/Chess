#pragma once

#include "ChessBoard.h"
#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>

class ChessBoardGUI : public QWidget
{
    Q_OBJECT
public:
    enum GameState {MovePiece, SelectPiece};
    explicit ChessBoardGUI(ChessBoard* boardLogic, QWidget *parent = nullptr);

private slots:
    void handleSquareClicked();

private:
    QGridLayout *m_gridLayout;
    QVector<QVector<QPushButton*>> m_boardSquares;
    ChessBoard *m_boardLogic;
    GameState m_gameState = GameState::SelectPiece;
    QPoint m_selectedPosition;

    void highlightSquareBlueBorder(const QPoint &position);
    void highlightSquareRedBorder(const QPoint &position);
    void drawPiece(const QPoint &position);
    void drawAllSquares();
    void drawAllPieces();
    void setupChessBoard();
signals:
};
