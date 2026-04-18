#include "ChessBoard.h"
#include "Rook.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "PiecesSetup.h"

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
    // m_grid = PiecesSetup::SetupNormal();
    m_grid = PiecesSetup::CustomSetup();
}

bool ChessBoard::tryMovePiece(const QPoint& from, const QPoint& to) const
{
    ChessPiece *piece = getPieceAt(from);
    if(!piece) return false;
    if(!piece->canMove(from, to)) return false;
    if(!isDestinationValid(from, to)) return false;
    // if(dynamic_cast<Bishop*>(piece)){
    switch(piece->type()){
        case ChessPiece::PieceType::Bishop:
            if(!isDiagonalPathClear(from, to)) return false; break;
        case ChessPiece::PieceType::Rook:
            if(!isStraightPathClear(from, to)) return false; break;
        case ChessPiece::PieceType::King:
            if(isGuardedByEnemy(piece->getColor(), to)) return false; break;
        case ChessPiece::PieceType::Queen:
            if(!isDiagonalPathClear(from, to) && !isStraightPathClear(from, to)) return false; break;
        case ChessPiece::PieceType::Pawn:
            if(!isPawnCaptureValid(from, to)) return false; break;
        default:
            return true;
    }

    return true;
}

void ChessBoard::movePiece(const QPoint& from, const QPoint& to)
{
    if(!tryMovePiece(from, to)) return;

    ChessPiece *piece = getPieceAt(from);
    ChessPiece *toPiece = getPieceAt(to);
    if(toPiece != nullptr) delete(toPiece);

    m_grid[to.y()][to.x()] = piece;
    m_grid[from.y()][from.x()] = nullptr;
    //if piece being moved is a Pawn
    if(dynamic_cast<Pawn*>(piece))
    {
        piece->setHasMovedTrue();
        piece = handlePromotion(to);
    }
}

void ChessBoard::restartBoard()
{
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            // if(m_grid[i][j] != nullptr){
                delete(m_grid[i][j]);
                m_grid[i][j] = nullptr;
            // }
        }
    }
    setupBoard();
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

ChessPiece* ChessBoard::handlePromotion(const QPoint &pos)
{
    ChessPiece *piece = getPieceAt(pos);
    ChessPiece::Color color = piece->getColor();
    int promotionY = (color == ChessPiece::White) ? 7 : 0;
    if(pos.y() == promotionY){
        delete piece;
        piece = new Queen(color);
        m_grid[pos.y()][pos.x()] = piece;
    }
    return piece;
}

bool ChessBoard::isGuardedByEnemy(ChessPiece::Color color, const QPoint &to) const
{
    ChessPiece::Color enemyColor = (color == ChessPiece::Color::White ? ChessPiece::Color::Black : ChessPiece::Color::White);
    for (int row=0; row<8; row++){
        for (int col = 0; col < 8; ++col) {
            QPoint from = QPoint(col, row);
            ChessPiece *piece = getPieceAt(from);
            if (!piece || piece->getColor() != enemyColor) continue; // rozpatrujemy tylko przeciwnika
            bool enemyPieceIsKing = dynamic_cast<King*>(piece);
            bool enemyPieceIsPawn= dynamic_cast<Pawn*>(piece);
            if (enemyPieceIsKing)
            {
                int dx = std::abs(to.x() - col);
                int dy = std::abs(to.y() - row);
                if (dx <= 1 && dy <= 1) return true;
            }
            else if (enemyPieceIsPawn)
            {
                int directionModifier = (color==ChessPiece::Color::White?-1:1);
                int dx = std::abs(to.x() - col);
                int dy = (to.y() - row) * directionModifier;
                if(dx==1 && dy==1) return true;
            }
            else if(ChessBoard::tryMovePiece(from, to)) return true;

        }
    }
    return false;
}


