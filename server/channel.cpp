#include "channel.h"
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlRecord>
#include <QJsonArray>

int Channel::login(const QString& username, const QString& password)
{
    QString hashed_password = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex();

    QSqlQuery query(db);
    query.prepare("SELECT id FROM Accounts WHERE username=:username AND password=:password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashed_password);
    query.exec();

    if (query.first())
        return query.value(0).toInt();

    return 0;
}

int Channel::signUp(const QString &username, const QString &password)
{
    QString hashed_password = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex();

    QSqlQuery query(db);
    query.prepare("INSERT INTO Accounts(username, password) VALUES(:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashed_password);
    query.exec();

    return query.lastInsertId().toInt();
}

QJsonDocument Channel::select(const QString &query_string)
{
    QSqlQuery query(db);
    query.exec(query_string);

    QJsonArray results;
    int result_number = 0;
    while (query.next())
    {
        QJsonArray data;
        for (int i = 0; i < query.record().count(); i++)
            data.append(query.value(i).toString());

        results.append(data);
        result_number++;
    }
    return QJsonDocument(results);
}

bool Channel::userExist(const QString &username)
{
    QSqlQuery query(db);
    query.prepare("SELECT EXISTS(SELECT 1 FROM Accounts WHERE username=:username)");
    query.bindValue(":username", username);
    query.exec();
    query.first();

    return query.value(0).toBool();
}

Channel::Channel(qintptr ID, QObject *parent) : QThread(parent)
{
    socketDescriptor = ID;

    db = QSqlDatabase::addDatabase("QSQLITE", QString::number(socketDescriptor));
    db.setDatabaseName("../database/HayDayDB.sqlite");
    db.open();
}

Channel::~Channel()
{
    db.close();
}

void Channel::run()
{
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
    QByteArray answer;
    if(data.startsWith("Login"))
    {
        data.remove("Login(");
        QString username = data.split(',')[0];
        QString password = data.split(',')[1];
        password.chop(1);
        qDebug() << "Logging in " << username << ":" << password;

        int account_id = login(username, password);
        answer.setNum(account_id);
        socket->write(answer);
    }
    else if(data.startsWith("Signup"))
    {
        data.remove("Signup(");
        QString username = data.split(',')[0];
        QString password = data.split(',')[1];
        password.chop(1);
        qDebug() << "Signing up " << username << ":" << password;

        int account_id = 0;
        if(!userExist(username))
            account_id = signUp(username, password);

        answer.setNum(account_id);
        socket->write(answer);
    }
    else if(data.startsWith("SELECT"))
    {
        socket->write(select(data).toJson());
    }
    else if(data.startsWith("INSERT"))
    {
        QSqlQuery query(db);
        query.exec(data);
        answer.setNum(query.lastInsertId().toInt());
        socket->write(answer);
    }
    else if(data.startsWith("UPDATE") || data.startsWith("DELETE"))
    {
        QSqlQuery query(db);
        query.exec(data);
    }
}

void Channel::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    exit(0);
}
