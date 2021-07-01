#include "farmer.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "globals.h"
#include <QDateTime>

int Farmer::id_ = 0;
Farmer *Farmer::farmer = nullptr;

Farmer::Farmer()
{
    coins_ = 20;
    level_ = 1;
    xp_ = 0;
    max_xp_ = 10;
    joining_date_ = QDateTime::currentDateTime().toTime_t();
}

Farmer &Farmer::get(int farmer_id)
{
    if (farmer == nullptr)
        farmer = new Farmer;

    if (farmer_id != farmer->id_)
    {
        farmer->id_ = farmer_id;

        QString query = "SELECT nickname, coins, level, xp, max_xp, joining_date, farm_id, account_id"
                        " FROM farmers WHERE id=:id";
        query.replace(":id", QString::number(farmer_id));

        socket.write(query);
        QJsonDocument servers_answer = QJsonDocument::fromJson(socket.read());

        if (!servers_answer.isNull())
        {
            QJsonObject json_obj = servers_answer.object();

            farmer->nickname_ = json_obj["0"].toString();
            farmer->coins_ = json_obj["1"].toInt();
            farmer->level_ = json_obj["2"].toInt();
            farmer->xp_ = json_obj["3"].toInt();
            farmer->max_xp_ = json_obj["4"].toInt();
            farmer->joining_date_ = static_cast<uint>(json_obj["5"].toInt());
            farmer->farm_id_ = json_obj["6"].toInt();
            farmer->account_id_ = json_obj["7"].toInt();
        }
        else
        {
            std::string err = "Farmer with id " + std::to_string(farmer_id) + " doesn't exist!";
            throw std::exception(err.c_str());
        }
    }

    return *farmer;
}

Farmer &Farmer::getByAccountId(int account_id)
{
    QString query = "SELECT id FROM Farmers WHERE account_id=:account_id";
    query.replace(":account_id", QString::number(account_id));

    socket.write(query);
    QJsonDocument servers_answer = QJsonDocument::fromJson(socket.read());

    if (!servers_answer.isNull())
    {
        return get(servers_answer.object()["0"].toInt());
    }
    else
    {
        std::string err = "Farmer with accountId " + std::to_string(account_id) + " doesn't exist!";
        throw std::exception(err.c_str());
    }
}

Farmer &Farmer::create(const QString& nickname, int account_id, int farm_id)
{
    if (farmer != nullptr)
        delete farmer;

    farmer = new Farmer;
    farmer->nickname_ = nickname;
    farmer->account_id_ = account_id;
    farmer->farm_id_ = farm_id;

    QString query = "INSERT INTO Farmers(nickname, account_id, farm_id, joining_date) VALUES(':nickname', :account_id, :farm_id, :joining_date)";
    query.replace(":nickname", nickname);
    query.replace(":account_id", QString::number(account_id));
    query.replace(":farm_id", QString::number(farm_id));
    query.replace(":joining_date", QString::number(farmer->joining_date_));

    socket.write(query);
    id_ = socket.read().toInt();

    return *farmer;
}

void Farmer::save() const
{
    QString query = "UPDATE Farmers SET nickname=':nickname', coins=:coins, "
                  "level=:level, xp=:xp, "
                  "max_xp=:max_xp, joining_date=:joining_date, farm_id=:farm_id, "
                  "account_id=:account_id "
                  "WHERE id=:id";

    query.replace(":id", QString::number(id_));
    query.replace(":nickname", nickname_);
    query.replace(":coins", QString::number(coins_));
    query.replace(":level", QString::number(level_));
    query.replace(":xp", QString::number(xp_));
    query.replace(":max_xp", QString::number(max_xp_));
    query.replace(":joining_date", QString::number(joining_date_));
    query.replace(":farm_id", QString::number(farm_id_));
    query.replace(":account_id", QString::number(account_id_));

    socket.write(query);
}
