#include "mainwindow.h"

#include <QWidget>
#include <QHBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_chessBoardLogic = new ChessBoard();
    m_chessBoard = new ChessBoardGUI();
    m_controller = new Controller(m_chessBoard, m_chessBoardLogic);
    QObject::connect(m_chessBoard, &ChessBoardGUI::cellClicked,
                     m_controller, &Controller::onCellClicked);


    QWidget *mainWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(mainWidget);
    QWidget *buttonsWidget = new QWidget(this);
    QVBoxLayout *buttonsLayout = new QVBoxLayout(buttonsWidget);
    // buttonsWidget->setLayout(buttonsLayout);

    layout->addWidget(m_chessBoard);
    layout->addWidget(buttonsWidget);
    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    QPushButton *restartButton = new QPushButton("restart", buttonsWidget);
    buttonsLayout->addWidget(restartButton);
    connect(restartButton, &QPushButton::clicked, this, [this](){onRestartPressed();});

    QPushButton *swapButton = new QPushButton("swap", buttonsWidget);
    buttonsLayout->addWidget(swapButton);
    connect(swapButton, &QPushButton::clicked, this, [this](){onSwapPressed();});

    buttonsLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

MainWindow::~MainWindow() {}

void MainWindow::onRestartPressed()
{
    m_controller->restart();
}

void MainWindow::onSwapPressed()
{
    m_chessBoard->swapSides();
    m_controller->updateView();
}
