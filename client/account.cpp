#include "account.h"
#include <QVariant>
#include <QSqlQuery>
#include "tcpsocket.h"

int Account::loginAndGetFarmerId(const QString &username, const QString &password)
{
    TcpSocket socket;
    socket.write("Login(" + username + "," + password + ")");
    int farmer_id = socket.read().toInt();
    return farmer_id;
}

int Account::signup(const QString &username, const QString &password)
{
    TcpSocket socket;
    socket.write("Signup(" + username + "," + password + ")");
    int account_id = socket.read().toInt();
    return account_id;
}
