#include "mainwindow.h"

#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_chessBoard = new ChessBoardGUI(new ChessBoard(), this);
    setCentralWidget(m_chessBoard);
}

MainWindow::~MainWindow() {}
