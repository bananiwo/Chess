#pragma once

#include "ChessBoardGUI.h"
#include "ChessBoard.h"

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(ChessBoardGUI *view, ChessBoard *model, QObject *parent = nullptr);
    void updateView();
    PieceData getPieceDataAt(const QPoint& pos) const;


private:
    ChessBoardGUI *m_view;
    ChessBoard *m_model;
    enum GameState {MovePiece, SelectPiece};
    GameState m_gameState = GameState::SelectPiece;
    QPoint m_selectedPos;


public slots:
    void onCellClicked(int row, int column);
};


