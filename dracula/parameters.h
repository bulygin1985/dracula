#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QString>
#include <QSet>

struct Parameters
{
    enum Mode
    {
        MULTI_PLAYER = 0,
        SINGLE_PLAYER = 1,
        TEST = 2,
        ALPHA = 3 //only implemented events, encounters
    };
    QString serverIP;
    int port;
    QSet<int> whoAreYou;
    bool isServer;
    Mode mode;
    Parameters()
    {
        isServer = false;
        serverIP = "127.0.0.1";
        port = 8888;
        mode = MULTI_PLAYER;
    }
    static Parameters& get()
    {
        static Parameters param;
        return param;
    }
};

#endif // PARAMETERS_H
