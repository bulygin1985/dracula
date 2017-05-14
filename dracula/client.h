#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

#include "logicobjects.h"

class Client : public QTcpSocket
{
    Q_OBJECT
public:
    Client();

public slots:
    void receiveData();
    void sendData(const Action & action);

private:
    QByteArray actionBytes;

signals:
    void actionIsReceived(Action action);
};

#endif // CLIENT_H
