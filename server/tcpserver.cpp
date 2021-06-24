#include "tcpserver.h"

void TcpServer::startServer()
{
    quint16 port = 8500;
    if(!this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening on port " << port << "...";
    }
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
        qDebug() << socketDescriptor << " Connecting...";
        Channel *channel = new Channel(socketDescriptor, this);
        connect(channel, SIGNAL(finished()), channel, SLOT(deleteLater()));
        channel->start();
}
