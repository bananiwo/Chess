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
    virtual bool isValidMove(const QPoint& from, const QPoint& to, ChessBoard* board) const = 0;
    Color getColor() const {return m_color;}

protected:
    Color m_color;
};
