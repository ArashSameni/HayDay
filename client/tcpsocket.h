#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>

class TcpSocket
{
    QTcpSocket socket_;
    void connectToServer();

public:
    TcpSocket();
    ~TcpSocket();

    void write(const QString &data);
    void write(const QByteArray &data);

    QByteArray read();
};

#endif // TCPSOCKET_H
