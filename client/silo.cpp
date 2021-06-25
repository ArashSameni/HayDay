#include "silo.h"
#include <QSqlQuery>
#include <QVariant>

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
    QSqlQuery query;
    query.prepare("INSERT INTO Silos DEFAULT VALUES");
    query.exec();

    id_ = query.lastInsertId().toInt();
    return *silo;
}

void Silo::save()
{
    QSqlQuery query;
    query.prepare("UPDATE Silos SET storage=:storage, max_storage=:max_storage, "
                  "upgrade_day=:upgrade_day, is_upgrading=:is_upgrading, level=:level "
                  "WHERE id=:id");
    query.bindValue(":id", id_);
    query.bindValue(":storage", storage_);
    query.bindValue(":max_storage", max_storage_);
    query.bindValue(":upgrade_day", upgrade_day_);
    query.bindValue(":is_upgrading", is_upgrading_);
    query.bindValue(":level", level_);
    query.exec();
}

Silo &Silo::get(int silo_id)
{
    if (silo == nullptr)
        silo = new Silo;

    if (silo_id != silo->id_)
    {
        silo->id_ = silo_id;

        QSqlQuery query;
        query.prepare("SELECT storage, max_storage, upgrade_day, is_upgrading, level FROM Silos WHERE id=:id");
        query.bindValue(":id", silo_id);
        query.exec();

        if (query.first())
        {
            silo->storage_ = query.value(0).toInt();
            silo->max_storage_ = query.value(1).toInt();
            silo->upgrade_day_ = query.value(2).toInt();
            silo->is_upgrading_ = query.value(3).toInt();
            silo->level_ = query.value(4).toInt();
        }
        else
        {
            std::string err = "Silo with id " + std::to_string(wheat_field_id) + " doesn't exist!";
            throw std::exception(err.c_str());
        }
    }

    return *silo;
}
