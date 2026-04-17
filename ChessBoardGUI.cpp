#include "ChessBoardGUI.h"
#include <QLabel>
#include <QChar>

ChessBoardGUI::ChessBoardGUI(QWidget *parent)
    : QWidget{parent}
{
    m_graphicsView = new QGraphicsView(this);
    m_scene = new QGraphicsScene(this);
    m_graphicsView->setScene(m_scene);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_graphicsView);
    setLayout(layout);
    loadIcons();
    setupChessBoard();
}


void ChessBoardGUI::setupChessBoard()
{
    const int boardSize = 8;
    const int squareSize = 85;

    m_scene->clear();
    m_boardSquares.resize(boardSize);
    for (int row = 0; row < boardSize; ++row)
    {
        m_boardSquares[row].resize(boardSize);

        for (int col = 0; col < boardSize; ++col)
        {
            QRectF rect(col * squareSize, row * squareSize, squareSize, squareSize);
            ChessSquareItem *square = new ChessSquareItem(row, col, rect);
            m_scene->addItem(square);
            square->onClicked = [this](int r, int c){handleSquareClicked(r, c);};
            m_boardSquares[row][col] = square;
            square->setFlag(QGraphicsItem::ItemIsSelectable);
            m_pieceItems[col][row] = nullptr;
        }
    }

    // Koordynaty pól planszy
    QFont font("Arial", 12, QFont::Bold);
    // Poziome (a-h)
    for (int col = 0; col < boardSize; ++col) {
        QGraphicsTextItem *label = m_scene->addText("", font);
        label->setDefaultTextColor(Qt::white);
        label->setPos(col * squareSize + squareSize / 2 - 5, boardSize * squareSize + 5);
        m_horizontalLabels[col] = label;
    }
    // Pionowe (1-8)
    for (int row = 0; row < boardSize; ++row) {
        QGraphicsTextItem *label = m_scene->addText("", font);
        label->setDefaultTextColor(Qt::white);
        label->setPos(-20, row * squareSize + squareSize / 2 - 10);
        m_verticalLabels[row] = label;
    }
    setLabels();

    int totalWidth  = boardSize * squareSize;
    int totalHeight = boardSize * squareSize + 40;

    m_scene->setSceneRect(-30, 0, totalWidth + 50, totalHeight);

    m_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_graphicsView->setFixedSize(m_scene->sceneRect().size().toSize());

    setFixedSize(m_graphicsView->size());
    foreach (auto a, m_boardSquares) {
        foreach (auto sq, a) {
            sq->setBrush(QBrush(QColorConstants::White));
        }

    }
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
        QString text = m_isBoardReversed ? QString(QChar('h' - col)) : QString(QChar('a' + col));
        m_horizontalLabels[col]->setPlainText(text);
    }
    for (int row = 0; row < 8; ++row) {
        QString text = m_isBoardReversed ? QString::number(row+1) : QString::number(8 - row);
        m_verticalLabels[row]->setPlainText(text);
    }
}

void ChessBoardGUI::handleSquareClicked(int row, int col)
{
    qDebug() << "clicked " << " row "<< row << " col " <<col;
    row = m_isBoardReversed ? (7-row) : row;
    col = m_isBoardReversed ? (7-col) : col;

    emit cellClicked(row, col);
}

void ChessBoardGUI::highlightSquareBlueBorder(QPoint position)
{
    QPoint pos = mirrorPointIfNeeded(position);
    m_boardSquares[pos.y()][pos.x()]->setHighlight(ChessSquareItem::Selected);
}

void ChessBoardGUI::highlightSquareRedBorder(QPoint position)
{
    QPoint pos = mirrorPointIfNeeded(position);
    m_boardSquares[pos.y()][pos.x()]->setHighlight(ChessSquareItem::AvailableMove);
}

void ChessBoardGUI::clearHighlights()
{
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            m_boardSquares[row][col]->setHighlight(ChessSquareItem::None);
        }
    }
}

void ChessBoardGUI::setPieceAt(QPoint pos, const PieceData& data)
{
    pos = mirrorPointIfNeeded(pos);
    // Remove old piece if exists
    if (m_pieceItems[pos.y()][pos.x()]) {
        delete m_pieceItems[pos.y()][pos.x()];
        m_pieceItems[pos.y()][pos.x()] = nullptr;
    }

    QPixmap pixmap;
    if (data.color == ChessPiece::White) {
        switch (data.type) {
        case PieceType::Pawn: pixmap = m_whitePawn.pixmap(80, 80); break;
        case PieceType::Rook: pixmap= m_whiteRook.pixmap(80,80); break;
        case PieceType::Knight: pixmap= m_whiteKnight.pixmap(80,80); break;
        case PieceType::Bishop: pixmap= m_whiteBishop.pixmap(80,80); break;
        case PieceType::Queen: pixmap= m_whiteQueen.pixmap(80,80); break;
        case PieceType::King: pixmap= m_whiteKing.pixmap(80,80); break;
        default: break;
        }
    } else {
        switch (data.type) {
        case PieceType::Pawn: pixmap = m_blackPawn.pixmap(80,80); break;
        case PieceType::Rook: pixmap = m_blackRook.pixmap(80,80); break;
        case PieceType::Knight: pixmap = m_blackKnight.pixmap(80,80); break;
        case PieceType::Bishop: pixmap = m_blackBishop.pixmap(80,80); break;
        case PieceType::Queen: pixmap = m_blackQueen.pixmap(80,80); break;
        case PieceType::King: pixmap = m_blackKing.pixmap(80,80); break;
        default: break;
        }
    }
    // Draw new piece
    QRectF squareRect = m_boardSquares[pos.y()][pos.x()]->rect();
    QGraphicsPixmapItem* pieceItem = m_scene->addPixmap(pixmap);
    pieceItem->setZValue(1);
    pieceItem->setPos(squareRect.topLeft() + QPointF((squareRect.width() - pixmap.width())/2,
                                                     (squareRect.height() - pixmap.height())/2));

    m_pieceItems[pos.y()][pos.x()] = pieceItem;
}
