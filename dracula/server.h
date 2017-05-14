#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

class Server: public QObject
{
    Q_OBJECT
public:
    Server();
    ~Server();
    void start();

public slots:
    void acceptConnection();
    void startRead();
    void socketStateIsChanged(QAbstractSocket::SocketState);

private:
    QTcpServer tspServer;
    QList<QTcpSocket*> socketList;

signals:
    void connectionIsAccepted();
};

#endif // SERVER_H
