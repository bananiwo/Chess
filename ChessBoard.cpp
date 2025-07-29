#include "ChessBoard.h"
#include "Rook.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include <iostream>
#include <qDebug>

ChessBoard::ChessBoard()
{
    m_board.resize(8);
    for(int i=0; i<8; i++)
    {
        m_board[i].resize(8);
    }
    setupBoard();
}

ChessPiece* ChessBoard::getPieceAt(const QPoint& pos) const
{
    return m_board[pos.y()][pos.x()];
}

void ChessBoard::setupBoard()
{

    qDebug("setupBoard - Logic");
    // setup white
    m_board[0][0] = new Rook(ChessPiece::White);
    m_board[0][1] = new Knight(ChessPiece::White);
    m_board[0][2] = new Bishop(ChessPiece::White);
    m_board[0][3] = new Queen(ChessPiece::White);
    m_board[0][4] = new King(ChessPiece::White);
    m_board[0][5] = new Bishop(ChessPiece::White);
    m_board[0][6] = new Knight(ChessPiece::White);
    m_board[0][7] = new Rook(ChessPiece::White);
    for(int i=0; i<8; i++)
    {
        m_board[1][i] = new Pawn(ChessPiece::White);
    }
    // setup black
    m_board[7][0] = new Rook(ChessPiece::Black);
    m_board[7][1] = new Knight(ChessPiece::Black);
    m_board[7][2] = new Bishop(ChessPiece::Black);
    m_board[7][3] = new Queen(ChessPiece::Black);
    m_board[7][4] = new King(ChessPiece::Black);
    m_board[7][5] = new Bishop(ChessPiece::Black);
    m_board[7][6] = new Knight(ChessPiece::Black);
    m_board[7][7] = new Rook(ChessPiece::Black);
    for(int i=0; i<8; i++)
    {
        m_board[6][i] = new Pawn(ChessPiece::Black);
    }
}

bool ChessBoard::movePiece(const QPoint& from, const QPoint& to)
{
    ChessPiece *piece = getPieceAt(from);
    if(!piece)
        return false;

    if(piece->isValidMove(from, to, this))
    {
        m_board[to.y()][to.x()] = piece;
        m_board[from.y()][from.x()] = nullptr;
        //if piece being moved is a Pawn
        if(dynamic_cast<Pawn*>(piece))
        {
            piece->setHasMovedTrue();
        }
        return true;
    }
    return false;
}
