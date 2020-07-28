#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include<vector>

/*------五子棋游戏模型类------*/
enum GameType
{
    MAN,//人人对战模式
    AI //人机对战模式
};

//游戏状态
enum GameStatus
{
    PALYING,
    WIN,
    DEAD
};


const int BOARD_GRAD_SIZE=15;//棋盘尺寸
const int MARGIN=30;//棋盘边缘空隙
const int CHESS_RADIUS=15;//棋子半径
const int MARK_SIZE=5;//落子标记边长
const int BLOCK_SIZE=40;//格子的大小
const int POS_OFFSET=BLOCK_SIZE*0.4;//鼠标点击的模糊距离
const int AI_THINK_TIME=700;//AI下棋的思考时间

class GameModel
{
public:
    GameModel();
public:
    //存储当前游戏棋盘和棋子的情况,空白为0.黑子1,白子-1
    std::vector<std::vector<int>> gameMapVec;

    //存储各个点位的评分情况,作为AI下的依据
    std::vector<std::vector<int>> scoreMapVec;

    //标识下棋方,true:黑棋方 false:AI 白棋方
    bool playerFlag;

    GameType gameType;//游戏模式
    GameStatus gameStatus;//游戏状态

    void startGame(GameType type);//开始游戏
    void calculateScore();//计算分数
    void actionByPerson(int row,int col);//人执行下棋
    void actionByAI(int &clickRow,int &clickCol);//机器执行下棋
    void updateGameMap(int row,int col);//每次落子后更新棋盘
    bool isWin(int row,int col);//判断游戏是否胜利
    bool isDeadGame();//判断是否和棋
};

#endif // GAMEMODEL_H
