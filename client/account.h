#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>

class Account
{
public:
    static int loginAndGetFarmerId(const QString &username, const QString &password);
    static int signup(const QString &username, const QString &password);
};

#endif // ACCOUNT_H
