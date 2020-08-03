#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "choosedialog.h"

#include <math.h>
#include <QMouseEvent>
#include <QBrush>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <qrandom.h>
#include <QtGlobal>
#include <QTime>
#include <QSound>

MainWindow::MainWindow(GameType mode,QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置窗口大小
    this->setFixedSize(MARGIN*2+BLOCK_SIZE*BOARD_GRAD_SIZE,
                       MARGIN*2+BLOCK_SIZE*BOARD_GRAD_SIZE);
    this->setMouseTracking(true);
    this->setWindowTitle("五子棋");
    initGame(mode);
}



MainWindow::~MainWindow()
{
    if(game){
         delete game;
    }
    delete ui;
}

void MainWindow::initAIGame()
{
    game->gameStatus=PALYING;
    //在数据模型中进行初始化功能
    game->startGame(game_type);
    update();
}

void MainWindow::chessOneByPerson()
{
    //根据当前存储的坐标下子
    //只有有效点击才下子,并且该处没有子
    if(clickPosRow!=-1&&clickPosCol!=-1&&game->gameMapVec[clickPosRow][clickPosCol]==0)
    {
        //在游戏的数据模型中落子
        game->actionByPerson(clickPosRow,clickPosCol);
        //播放落子音效
        QSound::play(":sound/chessone.wav");
        //重绘
        update();
    }
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

        //根据距离算出合适的点击位置,一共四个点,根据半径距离选最近的
        clickPosCol=-1;//初始化最终的值
        clickPosRow=-1;
        int len=0;//计算完最后取整就行了

        selectPos=false;

        //确定一个误差在范围内的点,且只可能确定一个出来
        //计算鼠标与所在方格左上角的距离
        len=sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY)*(y-leftTopPosY));
        if(len<POS_OFFSET)
        {
            clickPosCol=col;
            clickPosRow=row;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0)
            {
                selectPos=true;
            }
        }
        //计算鼠标与所在方格右上角的距离
        len=sqrt((x-leftTopPosX-BLOCK_SIZE)*(x-leftTopPosX-BLOCK_SIZE)+(y-leftTopPosY)*(y-leftTopPosY));
        if(len<POS_OFFSET)
        {
            clickPosCol=col+1;
            clickPosRow=row;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0)
            {
                selectPos=true;
            }
        }
        //计算鼠标与所在方格左下角的距离
        len=sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY-BLOCK_SIZE)*(y-leftTopPosY-BLOCK_SIZE));
        if(len<POS_OFFSET)
        {
            clickPosCol=col;
            clickPosRow=row+1;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0)
            {
                selectPos=true;
            }
        }
        //计算鼠标与所在方格右下角的距离
        len=sqrt((x-leftTopPosX-BLOCK_SIZE)*(x-leftTopPosX-BLOCK_SIZE)+(y-leftTopPosY-BLOCK_SIZE)*(y-leftTopPosY-BLOCK_SIZE));
        if(len<POS_OFFSET)
        {
            clickPosCol=col+1;
            clickPosRow=row+1;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0)
            {
                selectPos=true;
            }
        }
    }
    //再将屏幕刷新
     update();//调用paintEvent函数对界面进行重新绘制
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(selectPos==false)
        return;
    //在落子之前,把落子标记在设置为false;
    selectPos=false;
    chessOneByPerson();
    if(game_type==AI){//人机对战模式
        this->setMouseTracking(false);
        //AI下棋
    QTimer::singleShot(AI_THINK_TIME,this,SLOT(chessOneByAI()));
    }
}

void MainWindow::initGame(GameType gametype)
{
    this->game_type=gametype;
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
            //从上到下,第i+1条横线
            painter.drawLine(MARGIN,MARGIN+BLOCK_SIZE*i,
                             MARGIN+BLOCK_SIZE*BOARD_GRAD_SIZE,MARGIN+BLOCK_SIZE*i);
        }

        //绘制选中点
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        //绘制落子标记(防止鼠标出框越界)
        if(clickPosRow>0&&clickPosRow<BOARD_GRAD_SIZE
           &&clickPosCol>0&&clickPosCol<BOARD_GRAD_SIZE
           &&game->gameMapVec[clickPosRow][clickPosCol]==0)
        {
            if(game->playerFlag)
            {
                brush.setColor(Qt::black);
            }
            else
            {
                brush.setColor(Qt::white);
            }
            painter.setBrush(brush);
            painter.drawEllipse(MARGIN+BLOCK_SIZE*clickPosCol-MARK_SIZE,MARGIN+BLOCK_SIZE*clickPosRow-MARK_SIZE,MARK_SIZE*2,MARK_SIZE*2);
        }


        //绘制棋子
        for(int i=0;i<BOARD_GRAD_SIZE;++i){
            for(int j=0;j<BOARD_GRAD_SIZE;++j){
                if(game->gameMapVec[i][j]==1){
                    brush.setColor(Qt::black);
                    painter.setBrush(brush);
                    painter.drawEllipse(MARGIN+BLOCK_SIZE*j-CHESS_RADIUS,MARGIN+BLOCK_SIZE*i-CHESS_RADIUS,CHESS_RADIUS*2,CHESS_RADIUS*2);
                }
                else if(game->gameMapVec[i][j]==-1){
                    brush.setColor(Qt::white);
                    painter.setBrush(brush);
                    painter.drawEllipse(MARGIN+BLOCK_SIZE*j-CHESS_RADIUS,MARGIN+BLOCK_SIZE*i-CHESS_RADIUS,CHESS_RADIUS*2,CHESS_RADIUS*2);
                }
            }
        }

        //判断输赢
        if(clickPosCol>0&&clickPosCol<BOARD_GRAD_SIZE&&
           clickPosRow>0&&clickPosRow<BOARD_GRAD_SIZE&&
           (game->gameMapVec[clickPosRow][clickPosCol]==1||
                 game->gameMapVec[clickPosRow][clickPosCol]==-1))
        {
            QString str;
            if(game->isWin(clickPosRow,clickPosCol)//是否有赢家
                    &&game->gameStatus==PALYING)
            {
                game->gameStatus=WIN;
                if(game->gameMapVec[clickPosRow][clickPosCol]==1)
                    str="黑棋";
                else if(game->gameMapVec[clickPosRow][clickPosCol]==-1)
                    str="白棋";
                QSound::play(":sound/win.wav");
                QMessageBox::StandardButton btnValue=QMessageBox::information(NULL, "五子棋决战", str+"胜利!是否重新来一局?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                if(btnValue==QMessageBox::Yes)
                {
                     game->startGame(game_type);
                     game->gameStatus=PALYING;
                }
                else{
                     emit mainWindowClose();
                     this->close();
                }
            }
            if(game->isDeadGame()){//是否平局
                QMessageBox::StandardButton btnValue=QMessageBox::information(NULL, "五子棋决战", "平局!是否重新来一局?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                if(btnValue==QMessageBox::Yes)
                {
                     game->startGame(game_type);
                     game->gameStatus=PALYING;
                }
                else{
                     emit mainWindowClose();
                     this->close();
                }
            }

        }
}

void MainWindow::chessOneByAI()
{
    game->actionByAI(clickPosRow,clickPosCol);
    QSound::play(":sound/chessone.wav");
    update();
    this->setMouseTracking(true);
}
