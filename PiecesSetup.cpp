#include "PiecesSetup.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "Knight.h"

PiecesSetup::PiecesSetup() {}

QVector<QVector<ChessPiece*>> PiecesSetup::SetupNormal()
{
    QVector<QVector<ChessPiece*>> grid;
    grid.resize(8);
    for(int i=0; i<8; i++)
    {
        grid[i].resize(8);
    }
    // setup white
    grid[0][0] = new Rook(ChessPiece::White);
    grid[0][1] = new Knight(ChessPiece::White);
    grid[0][2] = new Bishop(ChessPiece::White);
    grid[0][3] = new Queen(ChessPiece::White);
    grid[0][4] = new King(ChessPiece::White);
    grid[0][5] = new Bishop(ChessPiece::White);
    grid[0][6] = new Knight(ChessPiece::White);
    grid[0][7] = new Rook(ChessPiece::White);
    for(int i=0; i<8; i++)
    {
        grid[1][i] = new Pawn(ChessPiece::White);
    }
    // setup black
    grid[7][0] = new Rook(ChessPiece::Black);
    grid[7][1] = new Knight(ChessPiece::Black);
    grid[7][2] = new Bishop(ChessPiece::Black);
    grid[7][3] = new Queen(ChessPiece::Black);
    grid[7][4] = new King(ChessPiece::Black);
    grid[7][5] = new Bishop(ChessPiece::Black);
    grid[7][6] = new Knight(ChessPiece::Black);
    grid[7][7] = new Rook(ChessPiece::Black);
    for(int i=0; i<8; i++)
    {
        grid[6][i] = new Pawn(ChessPiece::Black);
    }
    return grid;
}

QVector<QVector<ChessPiece *> > PiecesSetup::CustomSetup()
{
    QVector<QVector<ChessPiece*>> grid;
    grid.resize(8);
    for(int i=0; i<8; i++)
    {
        grid[i].resize(8);
    }
    // setup white
    // grid[0][0] = new Rook(ChessPiece::White);
    // grid[0][1] = new Knight(ChessPiece::White);
    // grid[0][2] = new Bishop(ChessPiece::White);
    // grid[0][3] = new Queen(ChessPiece::White);
    grid[0][4] = new King(ChessPiece::White);
    grid[0][5] = new Bishop(ChessPiece::White);
    grid[0][6] = new Knight(ChessPiece::White);
    grid[0][7] = new Rook(ChessPiece::White);
    for(int i=4; i<7; i++)
    {
        grid[6][i] = new Pawn(ChessPiece::White);
    }
    // setup black
    grid[7][0] = new Rook(ChessPiece::Black);
    grid[7][1] = new Knight(ChessPiece::Black);
    grid[7][2] = new Bishop(ChessPiece::Black);
    grid[7][3] = new Queen(ChessPiece::Black);
    grid[7][4] = new King(ChessPiece::Black);
    // grid[7][5] = new Bishop(ChessPiece::Black);
    // grid[7][6] = new Knight(ChessPiece::Black);
    // grid[7][7] = new Rook(ChessPiece::Black);
    for(int i=0; i<3; i++)
    {
        grid[2][i] = new Pawn(ChessPiece::Black);
    }
    return grid;
}
