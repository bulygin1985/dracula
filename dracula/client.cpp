#include "client.h"
#include "QsLog.h"

Client::Client()
{
    connect(this, SIGNAL(readyRead()), this, SLOT(receiveData()));

}

void Client::sendData(const Action &action)
{
    QLOG_INFO() << "Client::sendData(" + action.toQString() + ")";
    QByteArray actionSerialized;
    actionSerialized.push_back(action.type);
    actionSerialized.push_back(action.number);
    actionSerialized.push_back(action.who);
    actionSerialized.push_back(255); //it will be -1 as char
    QLOG_INFO() << "actionSerialized.size()= " << actionSerialized.size();
    for (int i = 0; i < actionSerialized.size(); i++)
        QLOG_INFO() << i << "=" << (int)actionSerialized[i];
    if (state() == QTcpSocket::ConnectedState)
    {
        write(actionSerialized);
    }
    else
    {
        QLOG_ERROR() << "Client is not connected!";
    }

}

void Client::receiveData()
{
    QLOG_DEBUG() << "Client::receiveData()";
    QByteArray data = readAll();
    actionBytes.push_back(data);
    if (actionBytes[actionBytes.length() - 1] == char(255))
    {
        QLOG_INFO() << "New action is received";
//        gameStateBytes.remove(gameStateBytes.length() - 1, 1);
        emit actionIsReceived(Action(actionBytes[0], actionBytes[1], actionBytes[2]));
        actionBytes.clear();
    }
}

