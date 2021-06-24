#include "channel.h"

int Channel::login(const QString& username, const QString& password)
{

}

Channel::Channel(qintptr ID, QMutex& mutex, QObject *parent) : QThread(parent),  mutex(mutex)
{
    socketDescriptor = ID;
}

void Channel::run()
{
    qDebug() << " Thread started";
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    qDebug() << socketDescriptor << " Client connected";
    exec();
}

void Channel::readyRead()
{
    QString data = socket->readAll();
    if(data.startsWith("Login"))
    {
        data.remove("Login(");
        QString username = data.split(',')[0];
        QString password = data.split(',')[1];
        password.truncate(password.size() - 1);

        data.setNum(login(username, password));
        socket->write(data.toUtf8());
    }
}

void Channel::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    exit(0);
}
