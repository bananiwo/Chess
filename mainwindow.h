#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include "ChessBoardGUI.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    ChessBoardGUI *m_chessBoard;
    ChessBoard *m_chessBoardLogic;
};
