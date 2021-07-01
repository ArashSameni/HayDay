#ifndef AUTH_H
#define AUTH_H

#include <QString>
#include "globals.h"
#include "tcpsocket.h"

class Auth
{
public:
    int loginAndGetFarmerId(const QString &username, const QString &password);
    int signup(const QString &username, const QString &password);
};

#endif // AUTH_H
