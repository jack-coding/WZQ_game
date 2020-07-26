#include"gamemodel.h"

GameModel::GameModel()
{

}

void GameModel::startGame(GameType type)
{
    gameType=type;
    //初始化棋盘
    gameMapVec.clear();
    for(int i=0;j<BOARD_GRAD_SIZE;i++){
        std::vector<int> lineBoard;
        for(int j=0;j<BOARD_GRAD_SIZE;++j){
            lineBoard.push_back(0);
            gameMapVec.push_back(lineBoard);
        }
    }
}

void GameModel::calculateScore()
{

}

void GameModel::actionByPerson(int row, int col)
{

}

void GameModel::actionByAI(int &clickRow, int &clickCol)
{

}

void GameModel::updateGameMap(int row, int col)
{

}

bool GameModel::isWin(int row, int col)
{

}

bool GameModel::isDeadGame()
{

}
