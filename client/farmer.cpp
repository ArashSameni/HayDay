#include "farmer.h"
#include <QJsonArray>
#include <QJsonDocument>
#include "globals.h"
#include <QDateTime>
#include "farm.h"

int Farmer::id_ = 0;
Farmer *Farmer::farmer = nullptr;

Farmer::Farmer()
{
    gender_ = 0;
    coins_ = 20;
    level_ = 1;
    xp_ = 0;
    max_xp_ = 10;
    joining_date_ = QDateTime::currentDateTime().toTime_t();
}

void Farmer::goNextLevel()
{
    xp_ -= max_xp_;
    max_xp_ += 10;
    level_ += 1;
    if(level_ == 3)
    {
        Barn &barn = Farm::get(farm_id_).barn();
        barn.addAlfalfa(1);
        barn.save();
    }
}

Farmer &Farmer::get(int farmer_id)
{
    if (farmer == nullptr)
        farmer = new Farmer;

    if (farmer_id != farmer->id_)
    {
        farmer->id_ = farmer_id;

        QString query = "SELECT nickname, gender, coins, level, xp, max_xp, joining_date, farm_id, account_id"
                        " FROM farmers WHERE id=:id";
        query.replace(":id", QString::number(farmer_id));

        socket.write(query);
        QJsonDocument servers_answer = QJsonDocument::fromJson(socket.read());

        if (!servers_answer.isNull())
        {
            QJsonArray data = servers_answer.array()[0].toArray();

            farmer->nickname_ = data[0].toString();
            farmer->gender_ = data[1].toString().toInt();
            farmer->coins_ = data[2].toString().toInt();
            farmer->level_ = data[3].toString().toInt();
            farmer->xp_ = data[4].toString().toInt();
            farmer->max_xp_ = data[5].toString().toInt();
            farmer->joining_date_ = data[6].toString().toUInt();
            farmer->farm_id_ = data[7].toString().toInt();
            farmer->account_id_ = data[8].toString().toInt();
        }
        else
        {
            QString err = "Farmer with id " + QString::number(farmer_id) + " doesn't exist!";
            throw err.toStdString().c_str();
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
        return get(servers_answer.array()[0].toArray()[0].toString().toInt());
    }
    else
    {
        QString err = "Farmer with accountId " + QString::number(account_id) + " doesn't exist!";
        throw err.toStdString().c_str();
    }
}

Farmer &Farmer::create(const QString& nickname, int gender, int account_id, int farm_id)
{
    if (farmer != nullptr)
        delete farmer;

    farmer = new Farmer;
    farmer->nickname_ = nickname;
    farmer->gender_ = gender;
    farmer->account_id_ = account_id;
    farmer->farm_id_ = farm_id;

    QString query = "INSERT INTO Farmers(nickname, gender, account_id, farm_id, joining_date) VALUES(':nickname', :gender, :account_id, :farm_id, :joining_date)";
    query.replace(":nickname", nickname);
    query.replace(":gender", QString::number(gender));
    query.replace(":account_id", QString::number(account_id));
    query.replace(":farm_id", QString::number(farm_id));
    query.replace(":joining_date", QString::number(farmer->joining_date_));

    socket.write(query);
    id_ = socket.read().toInt();

    return *farmer;
}

void Farmer::save() const
{
    QString query = "UPDATE Farmers SET nickname=':nickname', gender=:gender, coins=:coins, "
                  "level=:level, xp=:xp, "
                  "max_xp=:max_xp, joining_date=:joining_date, farm_id=:farm_id, "
                  "account_id=:account_id "
                  "WHERE id=:id";

    query.replace(":id", QString::number(id_));
    query.replace(":nickname", nickname_);
    query.replace(":gender", QString::number(gender_));
    query.replace(":coins", QString::number(coins_));
    query.replace(":level", QString::number(level_));
    query.replace(":xp", QString::number(xp_));
    query.replace(":max_xp", QString::number(max_xp_));
    query.replace(":joining_date", QString::number(joining_date_));
    query.replace(":farm_id", QString::number(farm_id_));
    query.replace(":account_id", QString::number(account_id_));

    socket.write(query);
}

bool Farmer::addXp(int amount)
{
    xp_ += amount;
    bool is_level_finished = xp_ >= max_xp_;
    if(is_level_finished)
        goNextLevel();

    save();
    return is_level_finished;
}
