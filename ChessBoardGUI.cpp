#include "ChessBoardGUI.h"
#include <QLabel>
#include <QChar>

ChessBoardGUI::ChessBoardGUI(QWidget *parent)
    : QWidget{parent}
{
    m_gridLayout = new QGridLayout();
    m_gridLayout->setSpacing(0);
    setLayout(m_gridLayout);
    loadIcons();
    setupChessBoard();
}


void ChessBoardGUI::setupChessBoard()
{
    const int boardSize = 8;
    m_boardSquares.resize(boardSize);

    for (int row = 0; row < boardSize; ++row) {
        m_boardSquares[row].resize(boardSize);

        for (int col = 0; col < boardSize; ++col) {
            QPushButton *square = new QPushButton(this);
            square->setFixedSize(85, 85);
            m_gridLayout->addWidget(square, row, col+1);
            m_boardSquares[row][col] = square;

            connect(square, &QPushButton::clicked, this, &ChessBoardGUI::handleSquareClicked);
            square->setProperty("row", row);
            square->setProperty("col", col);
        }
    }
    // Setup horizontal and vertical labels
    for (int row = 0; row < boardSize; ++row) {
        QLabel *label = new QLabel();
        label->setAlignment(Qt::AlignCenter);
        m_horizontalLabels[row] = label;
        m_gridLayout ->addWidget(label,8,row+1);
    }
    for (int col = 0; col < boardSize; ++col) {
        QLabel *label = new QLabel();
        label->setAlignment(Qt::AlignCenter);
        m_verticalLabels[col] = label;
        m_gridLayout ->addWidget(label,col, 0);
    }
    setLabels();
    drawAllSquares();
}

void ChessBoardGUI::loadIcons()
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

void ChessBoardGUI::swapSides()
{
    m_isBoardReversed = !m_isBoardReversed;
    setLabels();
}

QPoint ChessBoardGUI::mirrorPointIfNeeded(QPoint point)
{
    int revX = m_isBoardReversed ? (7-point.x()) : point.x();
    int revY = m_isBoardReversed ? (7-point.y()) : point.y();
    return QPoint(revX, revY);
}

void ChessBoardGUI::setLabels()
{
    for (int col = 0; col < 8; ++col) {
        QLabel *label =  m_horizontalLabels[col];
        QChar text = m_isBoardReversed ? QChar('H' - col) : QChar('A' + col);
        label->setText(QString(text));
    }
    for (int row = 0; row < 8; ++row) {
        QLabel *label =  m_verticalLabels[row];
        int number = m_isBoardReversed ? row+1 : 8-row;
        label->setText(QString::number(number));
    }
}

void ChessBoardGUI::handleSquareClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if(!clickedButton) return;

    int row = clickedButton->property("row").toInt();
    int col = clickedButton->property("col").toInt();
    row = m_isBoardReversed ? (7-row) : row;
    col = m_isBoardReversed ? (7-col) : col;

    emit cellClicked(row, col);
}

void ChessBoardGUI::highlightSquareBlueBorder(QPoint position)
{
    position = mirrorPointIfNeeded(position);
    QPushButton *square = m_boardSquares[position.y()][position.x()];
    if((position.x()+position.y())%2==0)
        square->setStyleSheet("background-color: white;"
                              "border: 2px solid blue");
    else
        square->setStyleSheet("background-color: gray;"
                              "border: 2px solid blue");
}

void ChessBoardGUI::highlightSquareRedBorder(QPoint position)
{
    position = mirrorPointIfNeeded(position);
    QPushButton *square = m_boardSquares[position.y()][position.x()];
    if((position.x()+position.y())%2==0)
        square->setStyleSheet("background-color: white;"
                               "border: 2px solid red"
                              );
    else
        square->setStyleSheet("background-color: gray;"
                               "border: 2px solid red"
                              );
}

void ChessBoardGUI::setPieceAt(QPoint pos, const PieceData& data)
{
    pos = mirrorPointIfNeeded(pos);
    QPushButton* square = m_boardSquares[pos.y()][pos.x()];
    QIcon icon;

    if (data.type == PieceType::None) {
        square->setIcon(QIcon());
        return;
    }

    if (data.color == ChessPiece::White) {
        switch (data.type) {
        case PieceType::Pawn: icon = m_whitePawn; break;
        case PieceType::Rook: icon = m_whiteRook; break;
        case PieceType::Knight: icon = m_whiteKnight; break;
        case PieceType::Bishop: icon = m_whiteBishop; break;
        case PieceType::Queen: icon = m_whiteQueen; break;
        case PieceType::King: icon = m_whiteKing; break;
        default: break;
        }
    } else {
        switch (data.type) {
        case PieceType::Pawn: icon = m_blackPawn; break;
        case PieceType::Rook: icon = m_blackRook; break;
        case PieceType::Knight: icon = m_blackKnight; break;
        case PieceType::Bishop: icon = m_blackBishop; break;
        case PieceType::Queen: icon = m_blackQueen; break;
        case PieceType::King: icon = m_blackKing; break;
        default: break;
        }
    }

    square->setIcon(icon);
    square->setIconSize(QSize(80, 80));
}
