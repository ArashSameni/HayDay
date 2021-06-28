#include "farm.h"
#include <QSqlQuery>
#include <QVariant>

int Farm::id_ = 0;
Farm *Farm::farm = nullptr;

Farm &Farm::get(int farm_id)
{
    if (farm == nullptr)
        farm = new Farm;

    if (farm_id != farm->id_)
    {
        farm->id_ = farm_id;

        QSqlQuery query;
        query.prepare("SELECT barn_id, silo_id, alfalfa_field_id, wheat_field_id FROM Farms WHERE id=:id");
        query.bindValue(":id", farm_id);
        query.exec();

        if (query.first())
        {
            farm->barn_id_ = query.value(0).toInt();
            farm->silo_id_ = query.value(1).toInt();
            farm->alfalfa_field_id_ = query.value(2).toInt();
            farm->wheat_field_id_ = query.value(3).toInt();
        }
        else
        {
            std::string err = "Farm with id " + std::to_string(farm_id) + " doesn't exist!";
            throw std::exception(err.c_str());
        }
    }

    return *farm;
}

Farm &Farm::create(int barn_id, int silo_id, int alfalfa_field_id, int wheat_field_id)
{
    if (farm != nullptr)
        delete farm;

    farm = new Farm;
    farm->barn_id_ = barn_id;
    farm->silo_id_ = silo_id;
    farm->alfalfa_field_id_ = alfalfa_field_id;
    farm->wheat_field_id_ = wheat_field_id;

    QSqlQuery query;
    query.prepare("INSERT INTO Farms(barn_id, silo_id, alfalfa_field_id, wheat_field_id) VALUES(:barn_id, :silo_id, :alfalfa_field_id, :wheat_field_id)");
    query.bindValue(":barn_id", barn_id);
    query.bindValue(":silo_id", silo_id);
    query.bindValue(":alfalfa_field_id", alfalfa_field_id);
    query.bindValue(":wheat_field_id", wheat_field_id);
    query.exec();

    id_ = query.lastInsertId().toInt();
    return *farm;
}
