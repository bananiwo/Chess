#pragma once
#include <QPoint>
//#include "ChessBoard.h"

class ChessBoard;

class ChessPiece
{
public:
    enum Color{White, Black};
    enum PieceType{Pawn, Rook, Bishop, Knight, Queen, King};

    ChessPiece(Color color) : m_color(color){}
    virtual ~ChessPiece(){}
    virtual bool canMove(const QPoint& from, const QPoint& to) const = 0;
    Color getColor() const {return m_color;}
    void setHasMovedTrue() {m_hasMoved = true;}
    virtual PieceType type() const = 0;

protected:
    Color m_color;
    bool m_hasMoved = false;
};
