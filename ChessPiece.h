#pragma once
#include <QPoint>
#include "ChessBoard.h"

class ChessBoard;

class ChessPiece
{
public:
    enum Color{White, Black};

    ChessPiece(Color color) : m_color(color){}
    virtual ~ChessPiece(){}
    virtual bool canMove(const QPoint& from, const QPoint& to) const = 0;
    Color getColor() const {return m_color;}
    void setHasMovedTrue() {m_hasMoved = true;}

protected:
    Color m_color;
    bool m_hasMoved = false;
};
