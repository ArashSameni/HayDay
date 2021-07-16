#include "silo.h"
#include <QJsonArray>
#include <QJsonDocument>
#include "globals.h"
#include <QDateTime>
#include "barn.h"
#include "farmer.h"
#include "farm.h"
#include <QtMath>
#include <QThread>

int Silo::id_ = 0;
Silo *Silo::silo = nullptr;

Silo::Silo() : Place(4)
{
    level_ = 1;
    upgrade_day_ = -1;
    is_upgrading_ = false;
    storage_ = 1;
    max_storage_ = 5;
}

Silo &Silo::create()
{
    if (silo != nullptr)
        delete silo;

    silo = new Silo;
    QString query = "INSERT INTO Silos DEFAULT VALUES";

    socket.write(query);
    id_ = socket.read().toInt();

    return *silo;
}

void Silo::save()
{
    QString query = "UPDATE Silos SET storage=:storage, max_storage=:max_storage, "
                    "upgrade_day=:upgrade_day, is_upgrading=:is_upgrading, level=:level "
                    "WHERE id=:id";
    query.replace(":id", QString::number(id_));
    query.replace(":storage", QString::number(storage_));
    query.replace(":max_storage", QString::number(max_storage_));
    query.replace(":upgrade_day", QString::number(upgrade_day_));
    query.replace(":is_upgrading", QString::number(is_upgrading_));
    query.replace(":level", QString::number(level_));

    socket.write(query);
}

int Silo::upgradeXp()
{
    return (level_ - 1) * 2;
}

bool Silo::isUpgradeFinished() const
{
    return CURRENT_DAY - static_cast<uint>(upgrade_day_) >= upgrade_time;
}

void Silo::finishUpgrade()
{
    max_storage_ *= 2;
    level_ += 1;
    is_upgrading_= false;
    save();
}

int Silo::isUpgradable(int farmer_id) const
{
    Farmer& farmer = Farmer::get(farmer_id);
    Barn& barn = Farm::get(farmer.farm_id()).barn();

    if(farmer.coins() < neededCoinsToUpgrade())
        return Enums::LACK_OF_COINS;
    if(barn.nails() < neededNailsToUpgrade())
        return Enums::LACK_OF_NAILS;
    if(barn.shovels() < neededShovelsToUpgrade())
        return Enums::LACK_OF_SHOVELS;
    if(level_ >= Farmer::get(farmer_id).level() - 1)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

Silo &Silo::get(int silo_id)
{
    if (silo == nullptr)
        silo = new Silo;

    if (silo_id != silo->id_)
    {
        silo->id_ = silo_id;

        QString query = "SELECT storage, max_storage, upgrade_day, is_upgrading, level FROM Silos WHERE id=:id";
        query.replace(":id", QString::number(silo_id));

        socket.write(query);
        QJsonDocument servers_answer = QJsonDocument::fromJson(socket.read());

        if (!servers_answer.isNull())
        {
            QJsonArray json_obj = servers_answer.array()[0].toArray();

            silo->storage_ = json_obj[0].toString().toInt();
            silo->max_storage_ = json_obj[1].toString().toInt();
            silo->upgrade_day_ = json_obj[2].toString().toInt();
            silo->is_upgrading_ = json_obj[3].toString().toInt();
            silo->level_ = json_obj[4].toString().toInt();
        }
        else
        {
            QString err = "Silo with id " + QString::number(silo_id) + " doesn't exist!";
            throw err.toStdString().c_str();
        }
    }

    return *silo;
}

int Silo::neededNailsToUpgrade() const
{
    return level_ * 2;
}

int Silo::neededShovelsToUpgrade() const
{
    return level_ - 1;
}

int Silo::neededCoinsToUpgrade() const
{
    return static_cast<int>(qPow((level_ * 2), 2) * 100);
}

void Silo::upgrade(Farmer& farmer, int barn_id)
{
    if(!is_upgrading_)
    {
        Barn& barn = Barn::get(barn_id);
        farmer.removeCoin(neededCoinsToUpgrade());
        farmer.save();
        QThread::msleep(10);

        barn.removeShovel(neededShovelsToUpgrade());
        barn.removeNail(neededNailsToUpgrade());
        barn.save();
        QThread::msleep(10);

        upgrade_day_ = static_cast<int>(CURRENT_DAY);
        is_upgrading_ = true;
        save();
    }
}
