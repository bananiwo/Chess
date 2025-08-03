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
    m_grid.resize(8);
    for(int i=0; i<8; i++)
    {
        m_grid[i].resize(8);
    }
    setupBoard();
}

ChessPiece* ChessBoard::getPieceAt(const QPoint& pos) const
{
    return m_grid[pos.y()][pos.x()];
}

void ChessBoard::setupBoard()
{
    // setup white
    m_grid[0][0] = new Rook(ChessPiece::White);
    m_grid[0][1] = new Knight(ChessPiece::White);
    m_grid[0][2] = new Bishop(ChessPiece::White);
    m_grid[0][3] = new Queen(ChessPiece::White);
    m_grid[0][4] = new King(ChessPiece::White);
    m_grid[0][5] = new Bishop(ChessPiece::White);
    m_grid[0][6] = new Knight(ChessPiece::White);
    m_grid[0][7] = new Rook(ChessPiece::White);
    for(int i=0; i<8; i++)
    {
        m_grid[1][i] = new Pawn(ChessPiece::White);
    }
    // setup black
    m_grid[7][0] = new Rook(ChessPiece::Black);
    m_grid[7][1] = new Knight(ChessPiece::Black);
    m_grid[7][2] = new Bishop(ChessPiece::Black);
    m_grid[7][3] = new Queen(ChessPiece::Black);
    m_grid[7][4] = new King(ChessPiece::Black);
    m_grid[7][5] = new Bishop(ChessPiece::Black);
    m_grid[7][6] = new Knight(ChessPiece::Black);
    m_grid[7][7] = new Rook(ChessPiece::Black);
    for(int i=0; i<8; i++)
    {
        m_grid[6][i] = new Pawn(ChessPiece::Black);
    }
}

bool ChessBoard::tryMovePiece(const QPoint& from, const QPoint& to)
{
    ChessPiece *piece = getPieceAt(from);
    if(!piece) return false;
    if(!piece->canMove(from, to)) return false;
    if(!isDestinationValid(from, to)) return false;
    if(dynamic_cast<Bishop*>(piece)){
        if(!isDiagonalPathClear(from, to)) return false;
    } else if(dynamic_cast<Rook*>(piece)){
        if(!isStraightPathClear(from, to)) return false;
    }  else if(dynamic_cast<Queen*>(piece)){
        if(!isDiagonalPathClear(from, to) && !isStraightPathClear(from, to)) return false;
    }  else if(dynamic_cast<Pawn*>(piece)){
        if(!isPawnCaptureValid(from, to)) return false;
    }

    return true;
}

void ChessBoard::movePiece(const QPoint& from, const QPoint& to)
{
    if(!tryMovePiece(from, to)) return;

    ChessPiece *piece = getPieceAt(from);
    // TODO: zniszczyć pion zbijany
    ChessPiece *toPiece = getPieceAt(to);
    if(toPiece != nullptr) delete(toPiece);

    m_grid[to.y()][to.x()] = piece;
    m_grid[from.y()][from.x()] = nullptr;
    //if piece being moved is a Pawn
    if(dynamic_cast<Pawn*>(piece))
    {
        piece->setHasMovedTrue();
        handlePromotion(to);
    }
}

bool ChessBoard::isDiagonalPathClear(const QPoint &from, const QPoint &to) const
{
    int dx = to.x () - from.x();
    int dy = to.y () - from.y();
    if(std::abs(dx) != std::abs(dy)) return false;
    int stepX = (dx>0) ? 1 : -1;
    int stepY = (dy>0) ? 1 : -1;
    int x = from.x() + stepX;
    int y = from.y() + stepY;
    while (x != to.x() && y != to.y())
    {
        if(getPieceAt(QPoint(x,y)) != nullptr) return false;

        x += stepX;
        y += stepY;
    }
    return true;
}
bool ChessBoard::isStraightPathClear(const QPoint &from, const QPoint &to) const
{
    int dx = to.x () - from.x();
    int dy = to.y () - from.y();
    if( dx * dy != 0) return false;

    int stepX = 0;
    int stepY = 0;
    if(dx!=0){
        stepX = (dx>0) ? 1 : -1;
    } else if(dy!=0){
        stepY = (dy>0) ? 1 : -1;
    }
    int x = from.x() + stepX;
    int y = from.y() + stepY;

    while (x != to.x() || y != to.y())
    {
        if(getPieceAt(QPoint(x,y)) != nullptr) return false;
        x += stepX;
        y += stepY;
    }
    return true;
}
bool ChessBoard::isDestinationValid(const QPoint &from, const QPoint &to) const
{
    ChessPiece *fromPiece = getPieceAt(from);
    ChessPiece *toPiece = getPieceAt(to);
    if(fromPiece == nullptr) return false;
    if(toPiece == nullptr) return true;
    return (fromPiece->getColor() != toPiece->getColor());
}
bool ChessBoard::isPawnCaptureValid(const QPoint &from, const QPoint &to) const
{
    ChessPiece *piece = getPieceAt(from);
    ChessPiece *otherPiece = getPieceAt(to);
    int dx = to.x() - from.x();
    int dy = to.y() - from.y();
    if(dx==0){
         if(getPieceAt(to) != nullptr) return false; // movement straight blocked
         return true; // move straight
    }
    if(std::abs(dx)==1
        && otherPiece != nullptr
        && otherPiece->getColor() != piece->getColor()) return true; // capture
    return false;
}

void ChessBoard::handlePromotion(const QPoint &pos)
{
    ChessPiece *piece = getPieceAt(pos);
    ChessPiece::Color color = piece->getColor();
    int promotionY = (color == ChessPiece::White) ? 7 : 0;
    if(pos.y() == promotionY){
        delete piece;
        piece = new Queen(color);
        m_grid[pos.y()][pos.x()] = piece;
    }
}


