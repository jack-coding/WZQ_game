#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMutex>
#include "gamemodel.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(GameType mode,QWidget *parent);
    ~MainWindow();
signals:
    void mainWindowClose();

private:
    Ui::MainWindow *ui;
    GameModel *game;//游戏指针
    GameType game_type=AI;//存储游戏类型
    int clickPosRow,clickPosCol;
    bool selectPos=false;//是否移动到合适的位置,已选中某个交叉点

    void initGame(GameType gametype);
    void initAIGame();
    void chessOneByPerson();
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    //绘制
    void paintEvent(QPaintEvent *event);
private slots:
    void chessOneByAI();
};

#endif // MAINWINDOW_H
