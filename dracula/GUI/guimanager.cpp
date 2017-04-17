#include "guimanager.h"
#include "QsLog.h"
#include "constants.h"

#include <QSet>
#include <assert.h>
#include <qmath.h>

Guimanager::Guimanager(GameState *gameState)
{
    QLOG_DEBUG() << " Guimanager constructor";
    this->gameState = gameState;
    phi.fill(0, PLAYER_AMOUNT);
}

void Guimanager::processAction(int num)
{
    QLOG_DEBUG() << " Guimanager::processAction(" << num << ")";
    emit action(Action(num));
}

void Guimanager::calcPlayersPhi()
{
    QLOG_DEBUG() << " Guimanager::paint";
    QSet<int> playerNum;
    playerNum << 0 << 1 << 2 << 3 << 4;             ///if player set to group - he is removed from playerNum set
    std::vector<std::vector<int> > groups;
    for (int i = DRACULA_NUM; i <= MINA_NUM; i++) // if are you dracula => 'i' starts from 0
    {
        if (playerNum.contains(i))
            {
            int currentNumber = gameState->getPlayer(i)->getLocationNum();
            std::vector<int> group;
            for (int j = i; j <= MINA_NUM; j++)
            {
                int number = gameState->getPlayer(j)->getLocationNum();
                if (number == currentNumber)
                {
                    group.push_back(j);
                    playerNum.remove(j);
                }
            }
            groups.push_back(group);
        }
    }
    for (uint i = 0; i < groups.size(); i++)
    {
        for (uint j = 0; j < groups[i].size(); j++)
        {
            int ind = groups[i][j];
            phi[ind] = (groups[i].size() == 1) ? -1 : 2 * M_PI * j / groups[i].size();
        }
    }
}
void Guimanager::paint(GameState *gameState)
{
    QLOG_DEBUG() << " Guimanager::paint";

    this->gameState = gameState;
    calcPlayersPhi();
    emit requestPaint();
}

int Guimanager::getPlayerLocation(int playerNum) const
{
    QLOG_DEBUG() << "Guimanager::getPlayerLocation(" << playerNum << ")";
    return gameState->getPlayer(playerNum)->getLocationNum();
}

int Guimanager::getWhoMoves() const
{
    return gameState->getWhoMovesNum();
}

double Guimanager::getPlayerPhi(int playerNum)
{
    assert(playerNum>=0 && playerNum <= PLAYER_AMOUNT);
    return phi[playerNum];
}

