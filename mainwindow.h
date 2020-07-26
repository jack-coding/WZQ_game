#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "gamemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    GameModel *game;//游戏指针
    GameType game_type;//存储游戏类型

    void initGame();
    void initAIGame();

    //绘制
    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
