#include "guimanager.h"
#include "QsLog.h"
#include "constants.h"
#include "logicobjects.h"
#include "loader.h"
#include "parameters.h"

#include <QSet>
#include <assert.h>
#include <qmath.h>

Guimanager::Guimanager(GameState *gameState, GameState * prevGameState)
{
    QLOG_DEBUG() << " Guimanager constructor";
    this->gameState = gameState;
    this->prevGameState = prevGameState;
    phi.fill(0, PLAYER_AMOUNT);

    draculaItems << "claws" << "dodge" << "escape_bat" << "escape_man" << "escape_mist" << "fangs" << "mesmerize" << "strength";
    QStringList hunterItems;
    hunterItems << "crucifix" << "stake" << "rifle";
    hunterItemsVector = QVector<QStringList>(4, hunterItems);
}

void Guimanager::processAction(int type, int num, int who) //TODO Enum class Type
{
    QLOG_INFO() << " Guimanager::processAction(type =" << type << ", num =" << num << ", who =" << who << " )";
    switch (type) {
    case 0:
        if (areYou(gameState->getWhoMovesNum()))
        {
            emit action(Action(type, num, who));
        }
        else
        {
            setWrongMessage("you cannot move " + gameState->getPlayer(gameState->getWhoMovesNum())->getName());
        }
        break;
    case 1:
        if (DRACULA_NUM == who)
        {
            draculaItems.removeAt(num);
        }
        else if (who >= LORD_NUM && who <=MINA_NUM)
        {
             hunterItemsVector[who - 1].removeAt(num);
        }
        break;
    }
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
void Guimanager::paint()
{
    QLOG_DEBUG() << " Guimanager::paint";
    calcPlayersPhi();
    emit requestPaint();
}

void Guimanager::setWrongMessage(QString message)
{
    emit wrongAction(message);
}

void Guimanager::setGameStates(GameState *gameState, GameState *prevGameState)
{
    this->gameState = gameState;
    this->prevGameState = prevGameState;
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

QList<int> Guimanager::getLocations(QString type)
{
    QLOG_DEBUG() << " Guimanager::getLocations";
    QList<int> locations;
    if ("track" == type)
    {
        for ( TrackElement& element : gameState->getDracula()->getTrack().getElements())
        {
            locations.push_back(element.location.number);
        }
    }
    else if ("catacombs" == type)
    {

    }
    return locations;
}

QList<bool> Guimanager::getOpenState(QString name)
{
    QList<bool> states;
    if ("track_locations" == name)
    {
        for ( TrackElement& element : gameState->getDracula()->getTrack().getElements())
        {
            states.push_back(element.location.isOpened);
        }
    }
    return states;
}

int Guimanager::getPlayerHealth(int playerNum) const
{
    QLOG_DEBUG() << "Guimanager::getPlayerHealth(" << playerNum << ")";
    return gameState->getPlayer(playerNum)->getHealth();

}

int Guimanager::getPlayerMaxHealth(int playerNum) const
{
    QLOG_DEBUG() << "Guimanager::getPlayerHealth(" << playerNum << ")";
    return gameState->getPlayer(playerNum)->getMaxHealth();
}

int Guimanager::getDayNightPosition() const
{
    return gameState->getDayNightPosition();
}

bool Guimanager::isTrackerChanged() const
{
    QLOG_DEBUG() << "Guimanager::isTrackerChanged()";
    if (prevGameState->getTrack() == gameState->getTrack())
    {
        return false;
    }
    return true;
}

QList<int> Guimanager::getPossibleLocations()
{
    QLOG_DEBUG() << "Guimanager::getPossibleLocations()";
//    QLOG_ERROR() << "getPossibleLocations = " << gameState->getWhoMoves()->getPossibleLocations();
    return gameState->getWhoMoves()->getPossibleLocations();
}

QPointF Guimanager::getLocationPoint(int i)
{
    return Loader::get().getLocationPoint(i);
}

QString Guimanager::getLocationName(int i, QString language)
{
    return Loader::get().getLocationName(i, language);
}

QStringList Guimanager::getEvents(int playerNum)
{
    assert((playerNum >= DRACULA_NUM) && (playerNum <= MINA_NUM));
    if (DRACULA_NUM == playerNum) return draculaItems;
    else return hunterItemsVector[playerNum-1];
}

bool Guimanager::areYou(int playerNum)
{
    QLOG_DEBUG() << "Guimanager::getWhoAreYou()";
    assert((playerNum >= DRACULA_NUM) && (playerNum <= MINA_NUM));
    return Parameters::get().whoAreYou.contains(playerNum);
}

void Guimanager::playGame()
{
    emit playClicked();
}

void Guimanager::backToMainMenu()
{
    QLOG_ERROR() << "Guimanager::backToMainMenu()";
    emit mainMenuClicked();
}

