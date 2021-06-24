#ifndef CHANNEL_H
#define CHANNEL_H

#include <QThread>
#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QMutex>

class Channel : public QThread
{
    Q_OBJECT

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    QMutex& mutex;
    int login(const QString& username, const QString& password);

public:
    explicit Channel(qintptr ID, QMutex& mutex, QObject *parent = nullptr);
    void run(void);

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();
};

#endif // CHANNEL_H
