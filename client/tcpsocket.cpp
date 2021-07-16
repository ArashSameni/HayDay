#include "tcpsocket.h"
#include "QThread"

TcpSocket::TcpSocket()
{
    connectToServer();
}

TcpSocket::~TcpSocket()
{
    socket_.disconnect();
}

QByteArray TcpSocket::read()
{
    socket_.waitForReadyRead(3000);
    return socket_.readAll();
}

void TcpSocket::write(const QString &data)
{
    write(data.toUtf8());
}

void TcpSocket::write(const QByteArray &data)
{
    socket_.write(data);
    socket_.waitForBytesWritten(1500);
    QThread::msleep(15);
}

void TcpSocket::connectToServer()
{
    socket_.connectToHost("127.0.0.1", 8500);
    if (!socket_.waitForConnected(3000))
        throw "Failed to connect to server.";
}
