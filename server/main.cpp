#include <QCoreApplication>
#include <QSqlDatabase>
#include "tcpserver.h"

bool initDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../database/HayDayDB.sqlite");
    return db.open();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if(!initDatabase())
    {
        qDebug() << "Error: Failed to connect to database.";
        exit(EXIT_FAILURE);
    }

    TcpServer Server;
    Server.startServer();

    return a.exec();
}
