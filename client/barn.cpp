#include "barn.h"
#include <QJsonArray>
#include <QJsonDocument>
#include "globals.h"
#include <QDateTime>
#include <QtMath>
#include <QThread>
int Barn::id_ = 0;
Barn *Barn::barn = nullptr;

Barn::Barn() : Place(5)
{
    storage_ = 1;
    max_storage_ = 5;
    shovels_ = 0;
    nails_ = 1;
    alfalfas_ = 0;
    eggs_ = 0;
    wools_ = 0;
    upgrade_day_ = -1;
    is_upgrading_ = false;
    level_ = 1;
}

Barn &Barn::get(int barn_id)
{
    if (barn == nullptr)
        barn = new Barn;

    if (barn_id != barn->id_)
    {
        barn->id_ = barn_id;
        barn->milks_.clear();

        QString query = "SELECT storage, max_storage, shovels, nails, alfalfas, eggs, wools, upgrade_day, "
                        "is_upgrading, level FROM Barns WHERE id=:id";
        query.replace(":id", QString::number(barn_id));

        socket.write(query);
        QJsonDocument servers_answer = QJsonDocument::fromJson(socket.read());

        if (!servers_answer.isNull())
        {
            QJsonArray datas = servers_answer.array()[0].toArray();
            barn->storage_ = datas[0].toString().toInt();
            barn->max_storage_ = datas[1].toString().toInt();
            barn->shovels_ = datas[2].toString().toInt();
            barn->nails_ = datas[3].toString().toInt();
            barn->alfalfas_ = datas[4].toString().toInt();
            barn->eggs_ = datas[5].toString().toInt();
            barn->wools_ = datas[6].toString().toInt();
            barn->upgrade_day_ = datas[7].toString().toInt();
            barn->is_upgrading_ = datas[8].toString().toInt();
            barn->level_ = datas[9].toString().toInt();

            query.clear();
            query = "SELECT id, manufacture_day, expiration_day"
                    " WHERE barn_id=:barn_id";
            query.replace(":barn_id", QString::number(barn_id));

            socket.write(query);
            servers_answer = QJsonDocument::fromJson(socket.read());

            Milk milk(barn_id);
            if (!servers_answer.isNull())
            {
                datas = servers_answer.array();
                for (int i = 0; i < datas.size(); i++)
                {
                    QJsonArray data = datas[i].toArray();
                    milk.setId(data[0].toString().toInt());
                    milk.setManufactureDay(data[1].toString().toInt());
                    milk.setExpirationDay(data[2].toString().toInt());

                    barn->milks_.push_back(milk);
                }
            }
        }
        else
        {
            QString err = "Barn with id " + QString::number(barn_id) + " doesn't exist!";
            throw err.toStdString().c_str();
        }
    }

    return *barn;
}

Barn &Barn::create()
{
    if (barn != nullptr)
        delete barn;

    barn = new Barn;
    QString query = "INSERT INTO Barns DEFAULT VALUES";

    socket.write(query);
    id_ = socket.read().toInt();
    return *barn;
}

void Barn::save() const
{
    QString query = "UPDATE Barns SET storage=:storage, max_storage=:max_storage, "
                    "shovels=:shovels, nails=:nails, alfalfas=:alfalfas, eggs=:eggs, wools=:wools, "
                    "upgrade_day=:upgrade_day, is_upgrading=:is_upgrading, level=:level "
                    "WHERE id=:id";

    query.replace(":storage", QString::number(id_));
    query.replace(":max_storage", QString::number(max_storage_));
    query.replace(":shovels", QString::number(shovels_));
    query.replace(":nails", QString::number(nails_));
    query.replace(":alfalfas", QString::number(alfalfas_));
    query.replace(":eggs", QString::number(eggs_));
    query.replace(":wools", QString::number(wools_));
    query.replace(":upgrade_day", QString::number(upgrade_day_));
    query.replace(":is_upgrading", QString::number(is_upgrading_));
    query.replace(":level", QString::number(level_));
    query.replace(":id", QString::number(id_));

    socket.write(query);
}

void Barn::checkMilksExpiration()
{
    QVector<Milk> milks;

    for (int i = 0; i < milks_.size(); i++)
    {
        if (milks_[i].isExpired())
            milks_[i].remove();
        else
            milks.push_back(milks_[i]);
    }

    milks_ = milks;
}

void Barn::addShovel(int amount)
{
    shovels_ += amount;
    storage_ += amount;
}

void Barn::addNail(int amount)
{
    nails_ += amount;
    storage_ += amount;
}

void Barn::addAlfalfa(int amount)
{
    alfalfas_ += amount;
    storage_ += amount;
}

void Barn::addEgg(int amount)
{
    eggs_ += amount;
    storage_ += amount;
}

void Barn::addWool(int amount)
{
    wools_ += amount;
    storage_ += amount;
}

void Barn::addMilk(const Milk &milk)
{
    milks_.push_back(milk);
    storage_ += 1;
}

void Barn::addMilk(int amount)
{
    for(int i=0;i<amount;i++)
    {
        Milk milk(id_);
        addMilk(milk);
        milk.save();
    }
}

void Barn::removeShovel(int amount)
{
    shovels_ -= amount;
    storage_ -= amount;
}

void Barn::removeNail(int amount)
{
    nails_ -= amount;
    storage_ -= amount;
}

void Barn::removeAlfalfa(int amount)
{
    alfalfas_ -= amount;
    storage_ -= amount;
}

void Barn::removeEgg(int amount)
{
    eggs_ -= amount;
    storage_ -= amount;
}

void Barn::removeWool(int amount)
{
    wools_ -= amount;
    storage_ -= amount;
}

void Barn::removeMilk(int amount)
{
    for (int i = 0; i < amount; i++)
    {
        milks_[i].remove();
        milks_.remove(i);
    }
    storage_ -= amount;
}

void Barn::removeMilk(const Milk &milk)
{
    for (int i = 0; i < milks_.size(); i++)
    {
        if (milks_[i].id() == milk.id())
        {
            milks_[i].remove();
            milks_.remove(i);
            break;
        }
    }
    storage_ -= 1;
}

void Milk::save()
{
    QString query = "INSERT INTO Milks(manufacture_day, expiration_day, barn_id)"
                    " VALUES(:manufacture_day, :expiration_day, :barn_id)";
    query.replace(":manufacture_day", QString::number(manufacture_day_));
    query.replace(":expiration_day", QString::number(expiration_day_));
    query.replace(":barn_id", QString::number(barn_id_));

    socket.write(query);
    id_ = socket.read().toInt();
}

void Milk::remove()
{
    QString query = "DELETE FROM Milks WHERE id=:id";
    query.replace(":id", QString::number(id_));
    socket.write(query);
}

bool Milk::isExpired()
{
    return static_cast<uint>(expiration_day_) <= CURRENT_DAY;
}

Milk::Milk(int barn_id)
{
    manufacture_day_ = static_cast<int>(CURRENT_DAY);
    expiration_day_ = manufacture_day_ + 10;
    barn_id_ = barn_id;
}

int Barn::upgradeXp()
{
    return (level_ - 1) * 3;
}

bool Barn::isUpgradeFinished() const
{
    return CURRENT_DAY - static_cast<uint>(upgrade_day_) >= upgrade_time;
}

void Barn::finishUpgrade()
{
    max_storage_ = qRound(1.5 * max_storage_);
    level_ += 1;
    is_upgrading_ = false;
    save();
}

int Barn::isUpgradable(int farmer_id) const
{
    Farmer& farmer = Farmer::get(farmer_id);
    if (farmer.coins() < neededCoinsToUpgrade())
        return Enums::LACK_OF_COINS;
    if (nails_ < neededNailsToUpgrade())
        return Enums::LACK_OF_NAILS;
    if (shovels_ < neededShovelsToUpgrade())
        return Enums::LACK_OF_SHOVELS;
    if (level_ >= Farmer::get(farmer_id).level())
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

void Barn::upgrade(Farmer& farmer, int barn_id)
{
    if (!is_upgrading_)
    {
        farmer.removeCoin(neededCoinsToUpgrade());
        farmer.save();
        QThread::msleep(10);

        removeShovel(neededShovelsToUpgrade());
        removeNail(neededNailsToUpgrade());

        upgrade_day_ = static_cast<int>(CURRENT_DAY);
        is_upgrading_ = true;
        save();
    }
}

int Barn::neededNailsToUpgrade() const
{
    return level_;
}

int Barn::neededShovelsToUpgrade() const
{
    return level_ - 1;
}

int Barn::neededCoinsToUpgrade() const
{
    return static_cast<int>(qPow(level_, 3) * 10);
}
