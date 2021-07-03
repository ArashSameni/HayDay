#include "auth.h"
#include <QVariant>
#include <QSqlQuery>
#include "tcpsocket.h"

int Auth::login(const QString &username, const QString &password)
{
    socket.write("Login(" + username.toLower() + "," + password + ")");
    int account_id = socket.read().toInt();
    return account_id;
}

int Auth::signup(const QString &username, const QString &password)
{
    socket.write("Signup(" + username.toLower() + "," + password + ")");
    int account_id = socket.read().toInt();
    return account_id;
}
