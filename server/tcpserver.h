#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QObject>
#include "channel.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT

private:
    QMutex mutex;
    void incomingConnection(qintptr socketDescriptor);

public:
    TcpServer() {}
    void startServer(void);
};

#endif // TCPSERVER_H
