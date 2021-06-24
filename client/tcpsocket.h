#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>

class TCPSocket
{
    QTcpSocket *socket_;
    void connectToServer(void);

public:
    TCPSocket();
    ~TCPSocket();

    void write(const QString &data);
    void write(const QByteArray &data);
    QByteArray read();
};

#endif // TCPSOCKET_H
