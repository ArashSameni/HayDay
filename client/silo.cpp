#include "silo.h"
#include <QJsonArray>
#include <QJsonDocument>
#include "globals.h"
#include <QDateTime>
#include "barn.h"
#include "farmer.h"

int Silo::id_ = 0;
Silo *Silo::silo = nullptr;

Silo::Silo()
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
    return upgrade_day_ - CURRENT_DAY >= 4;
}

void Silo::finishUpgrade()
{
    max_storage_ *= 2;
    level_ += 1;
    is_upgrading_= false;
    save();
}

bool Silo::isUpgradable(int farmer_id) const
{
    return level_ < Farmer::get(farmer_id).level() - 1;
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

int Silo::neededNailsToUpgrade(int barn_id) const
{
    return Barn::get(barn_id).level() * 2;
}

int Silo::neededShovelsToUpgrade(int barn_id) const
{
    return Barn::get(barn_id).level() - 2;
}

int Silo::neededCoinsToUpgrade(int barn_id) const
{
    return pow((Barn::get(barn_id).level() * 2), 2) * 100;
}

void Silo::upgrade()
{
    if(!is_upgrading_)
    {
        upgrade_day_ = CURRENT_DAY;
        is_upgrading_ = true;
    }
}
