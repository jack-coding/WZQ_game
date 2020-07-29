#include"gamemodel.h"

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

}

void GameModel::actionByPerson(int row, int col)
{
    updateGameMap(row,col);
}

void GameModel::actionByAI(int &clickRow, int &clickCol)
{

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
        if(row-k>0&&row-k+4<BOARD_GRAD_SIZE&&col+k>0&&col+k-4<BOARD_GRAD_SIZE&&
           gameMapVec[row-k][col+k]==gameMapVec[row-k+1][col+k-1]&&
           gameMapVec[row-k][col+k]==gameMapVec[row-k+2][col+k-2]&&
           gameMapVec[row-k][col+k]==gameMapVec[row-k+3][col+k-3]&&
           gameMapVec[row-k][col+k]==gameMapVec[row-k+4][col+k-4])
           return true;
    }
    //判断\方向是否有5个棋
    for(int k=0;k<5;++k){
        if(row+k>0&&row+k-4<BOARD_GRAD_SIZE&&col+k>0&&col+k-4<BOARD_GRAD_SIZE&&
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

}
