#include "tcpsocket.h"

TCPSocket::TCPSocket()
{
    connectToServer();
}

TCPSocket::~TCPSocket()
{
    socket_->disconnect();
}

QByteArray TCPSocket::read()
{
    socket_->waitForReadyRead(3000);
    return socket_->readAll();
}

void TCPSocket::write(const QString &data)
{
    write(data.toUtf8());
}

void TCPSocket::write(const QByteArray &data)
{
    socket_->write(data);
    socket_->waitForBytesWritten(1500);
}

void TCPSocket::connectToServer()
{
    socket_->connectToHost("127.0.0.1", 8500);
    if (!socket_->waitForConnected(3000))
        throw std::exception("Failed to connect to server.");
}
