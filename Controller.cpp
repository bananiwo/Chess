#include "Controller.h"
#include "PieceInfo.h"
#include "Rook.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"

Controller::Controller(ChessBoardGUI *view, ChessBoard *model, QObject *parent)
    : QObject{parent}, m_view(view), m_model(model)
{
    updateView();
}

void Controller::updateView()
{
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            QPoint pos(col, row);
            PieceData data = getPieceDataAt(pos);
            m_view->setPieceAt(pos, data);
        }
    }
}

void Controller::onCellClicked(int row, int column)
{
    QPoint pos(column, row);
    if(m_gameState == GameState::SelectPiece)
    {
        ChessPiece *piece = m_model->getPieceAt(pos);
        if(!piece) return;
        if(m_turn != piece->getColor()) return;
        m_selectedPos = pos;
        // highlight selected piece
        m_view->highlightSquareBlueBorder(pos);
        // highlight possible moves
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                QPoint toPosition(i, j);
                if(m_model->tryMovePiece(pos, toPosition))
                {
                    m_view->highlightSquareRedBorder(toPosition);
                }
            }
        }
        m_gameState = GameState::MovePiece;
    }
    else if (m_gameState == GameState::MovePiece)
    {
        ChessPiece *piece = m_model->getPieceAt(pos);
        if(m_model->tryMovePiece(m_selectedPos, pos))
        {   // on successful move
            m_model->movePiece(m_selectedPos, pos);
            m_turn = (m_turn == ChessPiece::Color::White ? ChessPiece::Color::Black : ChessPiece::Color::White);
        }
        else
        {   // on not successful move
        }
        m_view->clearHighlights();
        updateView();
        m_gameState = GameState::SelectPiece;
    }
}

PieceData Controller::getPieceDataAt(const QPoint& pos) const
{
    ChessPiece* piece = m_model->getPieceAt(pos);
    if (!piece) return {PieceType::None, ChessPiece::White}; // domyślnie

    if (dynamic_cast<Pawn*>(piece)) return {PieceType::Pawn, piece->getColor()};
    if (dynamic_cast<Rook*>(piece)) return {PieceType::Rook, piece->getColor()};
    if (dynamic_cast<Knight*>(piece)) return {PieceType::Knight, piece->getColor()};
    if (dynamic_cast<Bishop*>(piece)) return {PieceType::Bishop, piece->getColor()};
    if (dynamic_cast<Queen*>(piece)) return {PieceType::Queen, piece->getColor()};
    if (dynamic_cast<King*>(piece)) return {PieceType::King, piece->getColor()};

    return {PieceType::None, ChessPiece::White};
}

void Controller::restart()
{
    m_model->restartBoard();
    m_gameState = GameState::SelectPiece;
    m_turn = ChessPiece::Color::White;
    m_view->clearHighlights();
    updateView();
}
