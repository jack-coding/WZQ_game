#include"gamemodel.h"
#include<QTimer>
#include<QDebug>

GameModel::GameModel()
{

}

void GameModel::startGame(GameType type)
{
    gameType=type;
    //初始化棋盘
    gameMapVec.clear();
    for(int i=0;i<BOARD_GRAD_SIZE;i++)
    {
        std::vector<int> lineBoard;
        for(int j=0;j<BOARD_GRAD_SIZE;++j)
        {
            lineBoard.push_back(0);
        }
        gameMapVec.push_back(lineBoard);
    }

    //如果是AI模式,需要初始化评分数组
    if(gameType==AI)
    {
        scoreMapVec.clear();
        for(int i=0;i<BOARD_GRAD_SIZE;++i)
        {
            std::vector<int> lineScores;
            for(int j=0;j<BOARD_GRAD_SIZE;++j)
            {
                lineScores.push_back(0);
            }
            scoreMapVec.push_back(lineScores);
        }
    }

    //轮到黑方下棋为true,白方下棋为false
    playerFlag=true;

}

void GameModel::calculateScore()
{
    int emptyNum=0;//各个方向空白位的个数
    int botNum=0;//AI连成子的个数
    int personNum=0;//玩家连成子的个数
    //清空评分数组
    scoreMapVec.clear();
    for(int i=0;i<BOARD_GRAD_SIZE;++i)
    {
        std::vector<int> lineScores;
        for(int j=0;j<BOARD_GRAD_SIZE;++j)
        {
            lineScores.push_back(0);
        }
        scoreMapVec.push_back(lineScores);
    }

    //计分
    for(int row=0;row<BOARD_GRAD_SIZE;++row)
    {
        for(int col=0;col<BOARD_GRAD_SIZE;++col)
        {
            //空白点就算
            if(row>0&&col>0&&gameMapVec[row][col]==0){
                //遍历周围八个方向
                for(int y=-1;y<=1;++y)
                    for(int x=-1;x<=1;++x)
                    {
                        //重置
                        personNum=0;
                        botNum=0;
                        emptyNum=0;

                        //原坐标不算
                        if(!(y==0&&x==0))
                        {
                            //每个方向延伸4个子
                            //对玩家白子评分(正方向)
                            for(int i=1;i<=4;++i)
                            {
                                if(row+i*y>0&&row+i*y<BOARD_GRAD_SIZE&&col+i*x>0&&col+i*x<BOARD_GRAD_SIZE&&gameMapVec[row+i*y][col+i*x]==1)//玩家下的子
                                {
                                    ++personNum;
                                }
                                else if(row+i*y>0&&row+i*y<BOARD_GRAD_SIZE&&col+i*x>0&&col+i*x<BOARD_GRAD_SIZE&&gameMapVec[row+i*y][col+i*x]==0)
                                {
                                    ++emptyNum;
                                    break;
                                }
                                else//出界情况
                                    break;
                            }
                            //对玩家白子评分(反方向)
                            for(int i=1;i<=4;++i)
                            {
                                if(row-i*y>0&&row-i*y<BOARD_GRAD_SIZE&&col-i*x>0&&col-i*x<BOARD_GRAD_SIZE&&gameMapVec[row-i*y][col-i*x]==1)//玩家下的子
                                {
                                    ++personNum;
                                }
                                else if(row-i*y>0&&row-i*y<BOARD_GRAD_SIZE&&col-i*x>0&&col-i*x<BOARD_GRAD_SIZE&&gameMapVec[row-i*y][col-i*x]==0)
                                {
                                    ++emptyNum;
                                    break;
                                }
                                else//出界情况
                                    break;
                            }
                            if(personNum==1)
                                scoreMapVec[row][col]+=10;
                            else if(personNum==2)
                            {
                                if(emptyNum==1)
                                    scoreMapVec[row][col]+=30;
                                else if(emptyNum==2)
                                    scoreMapVec[row][col]+=40;
                            }
                            else if(personNum==3)
                            {
                                if(emptyNum==1)
                                    scoreMapVec[row][col]+=60;
                                else if(emptyNum==2)
                                    scoreMapVec[row][col]+=110;
                            }
                            else if(personNum==4)
                                scoreMapVec[row][col]+=10100;

                            emptyNum=0;
                            //对AI棋子评分
                            //每个方向延伸4个子
                            //对玩家白子评分(正方向)
                            for(int i=1;i<=4;++i)
                            {
                                if(row+i*y>0&&row+i*y<BOARD_GRAD_SIZE&&col+i*x>0&&col+i*x<BOARD_GRAD_SIZE&&gameMapVec[row+i*y][col+i*x]==-1)//玩家下的子
                                {
                                    ++botNum;
                                }
                                else if(row+i*y>0&&row+i*y<BOARD_GRAD_SIZE&&col+i*x>0&&col+i*x<BOARD_GRAD_SIZE&&gameMapVec[row+i*y][col+i*x]==0)
                                {
                                    ++emptyNum;
                                    break;
                                }
                                else//出界情况
                                    break;
                            }
                            //对玩家白子评分(反方向)
                            for(int i=1;i<=4;++i)
                            {
                                if(row-i*y>0&&row-i*y<BOARD_GRAD_SIZE&&col-i*x>0&&col-i*x<BOARD_GRAD_SIZE&&gameMapVec[row-i*y][col-i*x]==-1)//玩家下的子
                                {
                                    ++botNum;
                                }
                                else if(row-i*y>0&&row-i*y<BOARD_GRAD_SIZE&&col-i*x>0&&col-i*x<BOARD_GRAD_SIZE&&gameMapVec[row-i*y][col-i*x]==0)
                                {
                                    ++emptyNum;
                                    break;
                                }
                                else//出界情况
                                    break;
                            }
                            if(botNum==0)
                                scoreMapVec[row][col]+=5;
                            else if(botNum==1)
                                scoreMapVec[row][col]+=10;
                            else if(botNum==2)
                            {
                                if(emptyNum==1)
                                    scoreMapVec[row][col]+=25;
                                else if(emptyNum==2)
                                    scoreMapVec[row][col]+=50;
                            }
                            else if(botNum==3)
                            {
                                if(emptyNum==1)
                                    scoreMapVec[row][col]+=55;
                                else if(emptyNum==2)
                                    scoreMapVec[row][col]+=100;
                            }
                            else if(botNum>=4)
                                scoreMapVec[row][col]+=20100;
                        }
                    }
            }
        }
    }
}

void GameModel::actionByPerson(int row, int col)
{
      updateGameMap(row,col);
}

void GameModel::actionByAI(int &clickRow, int &clickCol)
{
    //计算评分
    calculateScore();
    int maxScore=0;
    std::vector<std::pair<int,int>>maxPoints;//保存分值最高的点的坐标
    for(int i=0; i<BOARD_GRAD_SIZE;++i)
    {
        for(int j=0;j<BOARD_GRAD_SIZE;++j)
        {
            if(scoreMapVec[i][j]>maxScore)
            {
                maxPoints.clear();
                maxScore=scoreMapVec[i][j];
                maxPoints.push_back(std::make_pair(i,j));
            }
            else if(scoreMapVec[i][j]==maxScore)
            {
                 maxPoints.push_back(std::make_pair(i,j));
            }
        }
    }
    //如果有多个分值最高点,随机挑选落子
    srand((unsigned)time(0));
    int index=rand()%maxPoints.size();
    std::pair<int,int> pos=maxPoints[index];

    //记录落子点
    clickRow=pos.first;
    clickCol=pos.second;
    updateGameMap(clickRow,clickCol);//刷新地图
}

void GameModel::updateGameMap(int row, int col)
{
    if(playerFlag)//如果是黑棋,将点坐标设为1
        gameMapVec[row][col]=1;
    else//如果是白棋,将点坐标设为-1
        gameMapVec[row][col]=-1;

    //换手
     playerFlag=!playerFlag;
}

bool GameModel::isWin(int row, int col)
{
    //判断水平方向是否有5个棋
    for(int i=0;i<5;++i){
        if(col-i>0&&col-i+4<BOARD_GRAD_SIZE&&
           gameMapVec[row][col-i]==gameMapVec[row][col-i+1]&&
           gameMapVec[row][col-i]==gameMapVec[row][col-i+2]&&
           gameMapVec[row][col-i]==gameMapVec[row][col-i+3]&&
           gameMapVec[row][col-i]==gameMapVec[row][col-i+4])
           return true;
    }
    //判断竖直方向是否有5个棋
    for(int j=0;j<5;++j){
        if(row-j>0&&row-j+4<BOARD_GRAD_SIZE&&
           gameMapVec[row-j][col]==gameMapVec[row-j+1][col]&&
           gameMapVec[row-j][col]==gameMapVec[row-j+2][col]&&
           gameMapVec[row-j][col]==gameMapVec[row-j+3][col]&&
           gameMapVec[row-j][col]==gameMapVec[row-j+4][col])
           return true;
    }
    //判断/方向是否有5个棋子
    for(int k=0;k<5;++k){
        if(row-k>0&&row-k+4<BOARD_GRAD_SIZE&&col+k-4>0&&col+k<BOARD_GRAD_SIZE&&
           gameMapVec[row-k][col+k]==gameMapVec[row-k+1][col+k-1]&&
           gameMapVec[row-k][col+k]==gameMapVec[row-k+2][col+k-2]&&
           gameMapVec[row-k][col+k]==gameMapVec[row-k+3][col+k-3]&&
           gameMapVec[row-k][col+k]==gameMapVec[row-k+4][col+k-4])
           return true;
    }
    //判断\方向是否有5个棋子
    for(int k=0;k<5;++k){
        if(row+k-4>0&&row+k<BOARD_GRAD_SIZE&&col+k-4>0&&col+k<BOARD_GRAD_SIZE&&
           gameMapVec[row+k][col+k]==gameMapVec[row+k-1][col+k-1]&&
           gameMapVec[row+k][col+k]==gameMapVec[row+k-2][col+k-2]&&
           gameMapVec[row+k][col+k]==gameMapVec[row+k-3][col+k-3]&&
           gameMapVec[row+k][col+k]==gameMapVec[row+k-4][col+k-4])
           return true;
    }
    return false;
}

bool GameModel::isDeadGame()
{
    for(int row=1;row<BOARD_GRAD_SIZE-1;++row)
    {
        for(int col=1;col<BOARD_GRAD_SIZE-1;++col)
        {
            if(!gameMapVec[row][col])
                return false;
        }
    }
    return true;
}
