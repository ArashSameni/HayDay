#ifndef CHANNEL_H
#define CHANNEL_H

#include <QThread>
#include <QObject>
#include <QDebug>
#include <QTcpSocket>

class Channel : public QThread
{
    Q_OBJECT

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    int login(const QString& username, const QString& password);

public:
    explicit Channel(qintptr ID, QObject *parent = nullptr);
    ~Channel();
    void run(void);

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();
};

#endif // CHANNEL_H
