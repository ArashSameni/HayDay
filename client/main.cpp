#include "mainwindow.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QApplication>

bool initDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../database/HayDayDB.sqlite");
    return db.open();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!initDatabase())
    {
        QMessageBox::critical(nullptr, "Error", "Failed to connect to database.");
        exit(0);
    }

    MainWindow w;
    w.show();

    return a.exec();
}
