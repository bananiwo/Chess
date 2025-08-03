#pragma once

#include "ChessPiece.h"

enum class PieceType {
    None, Pawn, Rook, Knight, Bishop, Queen, King
};

struct PieceData {
    PieceType type;
    ChessPiece::Color color;
};
