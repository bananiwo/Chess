#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include "ChessBoardGUI.h"
#include "Controller.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    ChessBoardGUI *m_chessBoard;
    ChessBoard *m_chessBoardLogic;
    Controller* m_controller;
};
