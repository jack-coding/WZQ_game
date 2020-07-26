#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置窗口大小
    this->setFixedSize(MARGIN*2+BLOCK_SIZE*BOARD_GRAD_SIZE,
                       MARGIN*2+BLOCK_SIZE*BOARD_GRAD_SIZE);
    initGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initAIGame()
{
    game_type=AI;
    game->gameStatus=PALYING;

    //在数据模型中进行初始化功能
    game->startGame(game_type);
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x=event->x();
    int y=event->y();

    if((x>=MARGIN+BLOCK_SIZE/2)&&(x<size().width()-MARGIN-BLOCK_SIZE/2)
       &&(y>=MARGIN+BLOCK_SIZE/2)&&(y<size().height()-MARGIN-BLOCK_SIZE/2))
    {
        //获取左上角在二维数组中的下标
        int col=(x-MARGIN)/BLOCK_SIZE;
        int row=(y-MARGIN)/BLOCK_SIZE;

        //获取左上角的像素坐标
        int leftTopPosX=MARGIN+col*BLOCK_SIZE;
        int leftTopPosY=MARGIN+row*BLOCK_SIZE;
    }

}

void MainWindow::initGame()
{
    game=new GameModel;
    initAIGame();
}



void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);//抗锯齿效果

    for(int i=0;i<BOARD_GRAD_SIZE+1;++i){//横线与竖线的数量均为格子数加一
        //从左到右,第i+1条竖线
        painter.drawLine(MARGIN+BLOCK_SIZE*i,MARGIN,
                         MARGIN+BLOCK_SIZE*i,MARGIN+BLOCK_SIZE*BOARD_GRAD_SIZE);
        //从上到下,第i+i条横线
        painter.drawLine(MARGIN,MARGIN+BLOCK_SIZE*i,
                         MARGIN+BLOCK_SIZE*BOARD_GRAD_SIZE,MARGIN+BLOCK_SIZE*i);
    }
}
