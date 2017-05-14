#include "server.h"
#include "QsLog.h"
#include "parameters.h"

Server::Server()
{
    QLOG_DEBUG() << "Server constructor";
}

void Server::start()
{
    QLOG_DEBUG() << "Server::start()";
    connect(&tspServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    tspServer.listen(QHostAddress::Any, Parameters::get().port);
    QLOG_DEBUG() << "Server are start on :";
    QLOG_DEBUG() << "IP :" << tspServer.serverAddress().toString();
    QLOG_DEBUG() << "Port : "<<tspServer.serverPort();
}

void Server::acceptConnection()
{
    QLOG_DEBUG() << "Server::acceptConnection()";
    QTcpSocket * tcpSocket = tspServer.nextPendingConnection();
    socketList.push_back(tcpSocket);
    QLOG_INFO() << "accept connection from : IP :" << tcpSocket->peerAddress().toString()
                << " ,port :" << tcpSocket->peerPort() << " ,ID : " << tcpSocket->socketDescriptor();
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(startRead()));
    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateIsChanged(QAbstractSocket::SocketState)));
    emit connectionIsAccepted();
}

void Server::startRead()
{
    QLOG_DEBUG() << "Server::startRead()";
    QObject * obj = sender();
    QTcpSocket * currentSocket = dynamic_cast<QTcpSocket *> (obj);
    QByteArray data = currentSocket->readAll();
    QLOG_INFO() <<"Server : recieved data from socket IP :" << currentSocket->peerAddress().toString()
               << " ,port :" << currentSocket->peerPort() << " ,ID : " << currentSocket->socketDescriptor();
    //QLOG_INFO() << data;
    for (QTcpSocket * socket : socketList)
    {
        if (socket->socketDescriptor() != currentSocket->socketDescriptor())
        {
            socket->write(data);
            QLOG_INFO() << "write to socket IP :" << socket->peerAddress().toString()
                        << " ,port :" << socket->peerPort() << " ,ID : " << socket->socketDescriptor();
        }
    }
}

void Server::socketStateIsChanged(QAbstractSocket::SocketState)
{
    QLOG_DEBUG() << "Server::socketStateIsChanged";
    if (tspServer.isListening())
    {
        for (QTcpSocket * socket : socketList)
        {
            if (socket->state() == QAbstractSocket::UnconnectedState)
            {
                QLOG_WARN() << "socket (IP :" << socket->peerAddress().toString()
                         << " ,port :" << socket->peerPort() << " ,ID : " << socket->socketDescriptor() << ") is unconnected";
                socketList.removeOne(socket);
            }
        }
    }
}

Server::~Server()
{
    QLOG_INFO() << "Server destructor";
    for (QTcpSocket * socket : socketList)
    {
        socket->close();
    }
    tspServer.close();
}
