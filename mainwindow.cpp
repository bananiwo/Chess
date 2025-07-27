#include "mainwindow.h"

#include <QWidget>
#include <QHBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_chessBoardLogic = new ChessBoard();
    m_chessBoard = new ChessBoardGUI(m_chessBoardLogic, this);
    QWidget *mainWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(mainWidget);
    layout->addWidget(m_chessBoard);
    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    QPushButton *button = new QPushButton("restart", this);
    layout->addWidget(button);
    connect(button, &QPushButton::clicked, this, [this](){m_chessBoardLogic->setupBoard();} );
    connect(button, &QPushButton::clicked, this, [this](){m_chessBoard->setupChessBoard();} );
}

MainWindow::~MainWindow() {}
