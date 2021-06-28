#include "auth.h"
#include <QVariant>
#include <QSqlQuery>
#include "tcpsocket.h"

int Auth::loginAndGetFarmerId(const QString &username, const QString &password)
{
    socket.write("Login(" + username + "," + password + ")");
    int farmer_id = socket.read().toInt();
    return farmer_id;
}

int Auth::signup(const QString &username, const QString &password)
{
    socket.write("Signup(" + username + "," + password + ")");
    int account_id = socket.read().toInt();
    return account_id;
}
