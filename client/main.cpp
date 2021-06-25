#include "mainwindow.h"
#include "globals.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QApplication>

int CURRENT_DAY;

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
        exit(EXIT_FAILURE);
    }

    MainWindow w;
    w.show();
    QSqlDatabase::database().close();
    return a.exec();
}
