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
    int clickPosRow,clickPosCol;
    bool selectPos=false;//是否移动到合适的位置,已选中某个交叉点
    void initGame();
    void initAIGame();
    void mouseMoveEvent(QMouseEvent *event);
    //绘制
    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
