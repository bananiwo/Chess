#pragma once
#include "ChessPiece.h"
#include <QPoint>

class NotationReporter
{
public:
    NotationReporter();
    static void Note(QPoint from, QPoint to, ChessPiece *piece, ChessPiece *toPiece);
};

