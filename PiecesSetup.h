#pragma once
#include <QVector>
#include "ChessPiece.h"

class PiecesSetup
{
public:
    PiecesSetup();
    static QVector<QVector<ChessPiece*>> SetupNormal();
    static QVector<QVector<ChessPiece*>> CustomSetup();
};


