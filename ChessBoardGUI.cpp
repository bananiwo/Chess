#include "ChessBoardGUI.h"
#include "Rook.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include <iostream>

ChessBoardGUI::ChessBoardGUI(ChessBoard* boardLogic, QWidget *parent)
    : m_boardLogic(boardLogic), QWidget{parent}
{
    m_gridLayout = new QGridLayout();
    m_gridLayout->setSpacing(0);
    setLayout(m_gridLayout);
    setupIcons();
    setupChessBoard();
}


void ChessBoardGUI::setupChessBoard()
{
    qDebug("setupChessBoard - GUI");
    const int boardSize = 8;
    m_boardSquares.resize(boardSize);

    for (int row = 0; row < boardSize; ++row) {
        m_boardSquares[row].resize(boardSize);

        for (int col = 0; col < boardSize; ++col) {
            QPushButton *square = new QPushButton(this);
            square->setFixedSize(85, 85);
            m_gridLayout->addWidget(square, row, col);
            m_boardSquares[row][col] = square;

            connect(square, &QPushButton::clicked, this, &ChessBoardGUI::handleSquareClicked);
            square->setProperty("row", row);
            square->setProperty("col", col);
        }
    }
    drawAllSquares();
    drawAllPieces();
}

void ChessBoardGUI::setupIcons()
{
    m_whitePawn = QIcon(":/images/images/white-pawn.png");
    m_whiteRook = QIcon(":/images/images/white-rook.png");
    m_whiteBishop = QIcon(":/images/images/white-bishop.png");
    m_whiteKnight = QIcon(":/images/images/white-knight.png");
    m_whiteQueen = QIcon(":/images/images/white-queen.png");
    m_whiteKing = QIcon(":/images/images/white-king.png");

    m_blackPawn = QIcon(":/images/images/black-pawn.png");
    m_blackRook = QIcon(":/images/images/black-rook.png");
    m_blackBishop = QIcon(":/images/images/black-bishop.png");
    m_blackKnight = QIcon(":/images/images/black-knight.png");
    m_blackQueen = QIcon(":/images/images/black-queen.png");
    m_blackKing = QIcon(":/images/images/black-king.png");
}

void ChessBoardGUI::drawAllSquares()
{
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QPushButton *square = m_boardSquares[row][col];
            if((row+col)%2==0)
                square->setStyleSheet("background-color: white;"
                                      "border-style: outset;"
                                      );
            else
                square->setStyleSheet("background-color: gray;"
                                      "border-style: outset;"
                                      );
        }
    }
}

void ChessBoardGUI::handleSquareClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if(!clickedButton) return;

    int row = clickedButton->property("row").toInt();
    int col = clickedButton->property("col").toInt();
    QPoint position(col, row);
    qDebug() << "button clicked at row " << row <<" col " << col;

    if(m_gameState == GameState::SelectPiece)
    {
        qDebug("GameState::SelectPiece");
        ChessPiece *piece = m_boardLogic->getPieceAt(QPoint(col, row));
        if(!piece) return;
        m_selectedPosition = QPoint(col, row);
        // highlight selected piece
        highlightSquareBlueBorder(m_selectedPosition);
        // highlight possible moves
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                QPoint toPosition(i, j);
                if(piece->isValidMove(QPoint(col, row), toPosition, m_boardLogic))
                {
                    highlightSquareRedBorder(toPosition);
                }
            }
        }
        m_gameState = GameState::MovePiece;
    }

    else if (m_gameState == GameState::MovePiece)
    {
        qDebug("GameState::MovePiece");
        // if(m_selectedPosition = QPoint::isNull()) return;

        ChessPiece *piece = m_boardLogic->getPieceAt(m_selectedPosition);
        if(piece->isValidMove(m_selectedPosition, QPoint(col, row), m_boardLogic))
        {
            m_boardLogic->movePiece(m_selectedPosition, QPoint(col,row));
        }
        else
        {
            qDebug("Not a valid move");
        }

        drawAllSquares();
        m_gameState = GameState::SelectPiece;
    }
    drawAllPieces();


}

void ChessBoardGUI::highlightSquareBlueBorder(const QPoint &position)
{
    QPushButton *square = m_boardSquares[position.y()][position.x()];
    if((position.x()+position.y())%2==0)
        square->setStyleSheet("background-color: white;"
                              "border: 2px solid blue");
    else
        square->setStyleSheet("background-color: gray;"
                              "border: 2px solid blue");
}

void ChessBoardGUI::highlightSquareRedBorder(const QPoint &position)
{
    QPushButton *square = m_boardSquares[position.y()][position.x()];
    if((position.x()+position.y())%2==0)
        square->setStyleSheet("background-color: yellow;"
                              // "border: 1px solid red"
                              );
    else
        square->setStyleSheet("background-color: yellow;"
                              // "border: 1px solid red"
                              );
}

void ChessBoardGUI::drawPiece(const QPoint &position)
{
        QSize iconSize(80, 80);
        ChessPiece *piece = m_boardLogic->getPieceAt(position);
        QPushButton *square = m_boardSquares[position.y()][position.x()];
        QIcon icon;
        if(dynamic_cast<Pawn*>(piece)){
            icon = (piece->getColor()==ChessPiece::Color::White ? m_whitePawn : m_blackPawn);
        }
        else if(dynamic_cast<Rook*>(piece)){
            icon = (piece->getColor()==ChessPiece::Color::White ? m_whiteRook : m_blackRook);
        }
        else if(dynamic_cast<Bishop*>(piece)){
            icon = (piece->getColor()==ChessPiece::Color::White ? m_whiteBishop: m_blackBishop);
        }
        else if(dynamic_cast<Knight*>(piece)){
            icon = (piece->getColor()==ChessPiece::Color::White ? m_whiteKnight : m_blackKnight);
        }
        else if(dynamic_cast<Queen*>(piece)){
            icon = (piece->getColor()==ChessPiece::Color::White ? m_whiteQueen: m_blackQueen);
        }
        else if(dynamic_cast<King*>(piece)){
            icon = (piece->getColor()==ChessPiece::Color::White ? m_whiteKing: m_blackKing);
        }
        // else {
        //     square->setIcon(QIcon());
        // }
        square->setIcon(icon);
        square->setIconSize(iconSize);
}

void ChessBoardGUI::drawAllPieces()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            drawPiece(QPoint(i, j));
        }
    }
}
