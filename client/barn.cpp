#include "barn.h"
#include <QSqlQuery>
#include <QVariant>
#include "globals.h"

Barn::Barn()
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

        QSqlQuery query;
        query.prepare("SELECT storage, max_storage, shovels, nails, alfalfas, eggs, wools, upgrade_day, "
                      "is_upgrading, level FROM Barns WHERE id=:id");
        query.bindValue(":id", barn_id);
        query.exec();

        if (query.first())
        {
            barn->storage_ = query.value(0).toInt();
            barn->max_storage_ = query.value(1).toInt();
            barn->shovels_ = query.value(2).toInt();
            barn->nails_ = query.value(3).toInt();
            barn->alfalfas_ = query.value(4).toInt();
            barn->eggs_ = query.value(5).toInt();
            barn->wools_ = query.value(6).toInt();
            barn->upgrade_day_ = query.value(7).toInt();
            barn->is_upgrading_ = query.value(8).toInt();
            barn->level_ = query.value(9).toInt();

            query.clear();
            query.prepare("SELECT id, manufacture_day, expiration_day"
                          " WHERE barn_id=:barn_id");
            query.bindValue(":barn_id", barn_id);
            query.exec();

            Milk milk(barn_id);
            while (query.next())
            {
                milk.setId(query.value(0).toInt());
                milk.setManufactureDay(query.value(1).toInt());
                milk.setExpirationDay(query.value(0).toInt());

                barn->milks_.push_back(milk);
            }
        }
        else
        {
            std::string err = "Barn with id " + std::to_string(barn_id) + " doesn't exist!";
            throw std::exception(err.c_str());
        }
    }

    return *barn;
}

Barn &Barn::create()
{
    if (barn != nullptr)
        delete barn;

    barn = new Barn;
    QSqlQuery query;
    query.prepare("INSERT INTO Barns DEFAULT VALUES");
    query.exec();

    id_ = query.lastInsertId().toInt();
    return *barn;
}

void Barn::save()
{
    QSqlQuery query;
    query.prepare("UPDATE Barns SET storage=:storage, max_storage=:max_storage, "
                  "shovels=:shovels, nails=:nails, alfalfas=:alfalfas, eggs=:eggs, wools=:wools, "
                  "upgrade_day=:upgrade_day, is_upgrading=:is_upgrading, level=:level "
                  "WHERE id=:id");

    query.bindValue(":storage", id_);
    query.bindValue(":max_storage", max_storage_);
    query.bindValue(":shovels", shovels_);
    query.bindValue(":nails", nails_);
    query.bindValue(":alfalfas", alfalfas_);
    query.bindValue(":eggs", eggs_);
    query.bindValue(":wools", wools_);
    query.bindValue(":upgrade_day", upgrade_day_);
    query.bindValue(":is_upgrading", is_upgrading_);
    query.bindValue(":level", level_);
    query.exec();
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

void Barn::addMilk(Milk milk)
{
    milks_.push_back(milk);
    storage_ += 1;
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

void Barn::removeMilk(int milk_id)
{
    for (int i = 0; i < milks_.size(); i++)
    {
        if (milks_[i].id() == milk_id)
        {
            milks_[i].remove();
            milks_.remove(i);
            break;
        }
    }
    storage_ -= 1;
}

void Barn::removeMilk(Milk milk)
{
    removeMilk(milk.id());
}

void Milk::save()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Milks(manufacture_day, expiration_day, barn_id) VALUES(:manufacture_day, :expiration_day, :barn_id)");
    query.bindValue(":manufacture_day", manufacture_day_);
    query.bindValue(":expiration_day", expiration_day_);
    query.bindValue(":barn_id", barn_id_);
    query.exec();

    id_ = query.lastInsertId().toInt();
}

void Milk::remove()
{
    QSqlQuery query;
    query.prepare("DELETE FROM Milks WHERE id=:id");
    query.bindValue(":id", id_);
    query.exec();
}

bool Milk::isExpired()
{
    return expiration_day_ > CURRENT_DAY;
}

Milk::Milk(int barn_id)
{
    manufacture_day_ = CURRENT_DAY;
    expiration_day_ = CURRENT_DAY + 10;
    barn_id_ = barn_id;
}
