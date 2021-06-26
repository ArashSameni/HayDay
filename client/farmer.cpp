#include "farmer.h"
#include <QDateTime>
#include <QSqlQuery>
#include <QVariant>

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

        QSqlQuery query;
        query.prepare("SELECT nickname, coins, level, xp, max_xp, joining_date, farm_id, account_id FROM farmers WHERE id=:id");
        query.bindValue(":id", farmer_id);
        query.exec();

        if (query.first())
        {
            farmer->nickname_ = query.value(0).toString();
            farmer->coins_ = query.value(1).toInt();
            farmer->level_ = query.value(2).toInt();
            farmer->xp_ = query.value(3).toInt();
            farmer->max_xp_ = query.value(4).toInt();
            farmer->joining_date_ = query.value(5).toUInt();
            farmer->farm_id_ = query.value(6).toInt();
            farmer->account_id_ = query.value(7).toInt();
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
    QSqlQuery query;
    query.prepare("SELECT id"
                  " FROM Farmers WHERE account_id=:account_id");
    query.bindValue(":account_id", account_id);
    query.exec();

    if (query.first())
    {
        return get(query.value(0).toInt());
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

    QSqlQuery query;
    query.prepare("INSERT INTO Farmers(nickname, account_id, farm_id, joining_date) VALUES(:nickname, :account_id, :farm_id, :joining_date)");
    query.bindValue(":nickname", nickname);
    query.bindValue(":account_id", account_id);
    query.bindValue(":farm_id", farm_id);
    query.bindValue(":joining_date", farmer->joining_date_);
    query.exec();

    id_ = query.lastInsertId().toInt();
    return *farmer;
}

void Farmer::save() const
{
    QSqlQuery query;
    query.prepare("UPDATE Farmers SET nickname=:nickname, coins=:coins, "
                  "level=:level, xp=:xp, "
                  "max_xp=:max_xp, joining_date=:joining_date, farm_id=:farm_id, "
                  "account_id=:account_id "
                  "WHERE id=:id");

    query.bindValue(":id", id_);
    query.bindValue(":nickname", nickname_);
    query.bindValue(":coins", coins_);
    query.bindValue(":level", level_);
    query.bindValue(":xp", xp_);
    query.bindValue(":max_xp", max_xp_);
    query.bindValue(":joining_date", joining_date_);
    query.bindValue(":farm_id", farm_id_);
    query.bindValue(":account_id", account_id_);
    query.exec();
}
