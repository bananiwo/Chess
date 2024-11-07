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

    void highlightSquareBlueBorder(const QPoint &position);
    void highlightSquareRedBorder(const QPoint &position);
    void drawPiece(const QPoint &position);
    void drawAllSquares();
    void drawAllPieces();
    void setupChessBoard();
    void setupIcons();
signals:
};
