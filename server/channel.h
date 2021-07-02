#ifndef CHANNEL_H
#define CHANNEL_H

#include <QThread>
#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QSqlDatabase>

class Channel : public QThread
{
    Q_OBJECT

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    QSqlDatabase db;
    int login(const QString& username, const QString& password);
    int signUp(const QString& username, const QString& password);
    QJsonDocument select(const QString& query_string);
    bool userExist(const QString& username);

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
