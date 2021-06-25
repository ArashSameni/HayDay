#include "livingplaces.h"
#include <QSqlQuery>
#include <QVariant>

void LivingPlace::get(LivingPlace &living_place, int living_place_id)
{
    QSqlQuery query;
    query.prepare("SELECT type, storage, max_storage, animals_condition, feeding_day, upgrade_day, is_upgrading, level, farm_id"
                  " FROM LivingPlaces WHERE id=:id");
    query.bindValue(":id", living_place_id);
    query.exec();

    if (query.first())
    {
        living_place.type_ = query.value(0).toInt();
        living_place.storage_ = query.value(1).toInt();
        living_place.max_storage_ = query.value(2).toInt();
        living_place.animals_condition_ = query.value(3).toInt();
        living_place.feeding_day_ = query.value(4).toInt();
        living_place.upgrade_day_ = query.value(5).toInt();
        living_place.is_upgrading_ = query.value(6).toInt();
        living_place.level_ = query.value(7).toInt();
        living_place.farm_id_ = query.value(8).toInt();
    }
    else
    {
        std::string err = "LivingPlace with id " + std::to_string(living_place_id) + " doesn't exist!";
        throw std::exception(err.c_str());
    }
}

int LivingPlace::getLivingPlaceIdByFarmId(int farm_id, int type)
{
    QSqlQuery query;
    query.prepare("SELECT id"
                  " FROM LivingPlaces WHERE farm_id=:farm_id AND type=:type");
    query.bindValue(":farm_id", farm_id);
    query.bindValue(":type", type);
    query.exec();

    if (query.first())
    {
        return query.value(0).toInt();
    }
    else
    {
        std::string err = "LivingPlace with farmId " + std::to_string(farm_id) + " and type " + std::to_string(type) + " doesn't exist!";
        throw std::exception(err.c_str());
    }
}

int LivingPlace::create(int farm_id, int type)
{
    QSqlQuery query;
    query.prepare("INSERT INTO LivingPlaces(type, farm_id) VALUES(:type, :farm_id)");
    query.bindValue(":type", type);
    query.bindValue(":farm_id", farm_id);
    query.exec();

    return query.lastInsertId().toInt();
}

void LivingPlace::save(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE LivingPlaces SET type=:type, storage=:storage, "
                  "max_storage=:max_storage, animals_condition=:animals_condition, "
                  "feeding_day=:feeding_day, upgrade_day=:upgrade_day, is_upgrading=:is_upgrading. "
                  "level=:level, farm_id=:farm_id "
                  "WHERE id=:id");

    query.bindValue(":id", id);
    query.bindValue(":type", type_);
    query.bindValue(":storage", storage_);
    query.bindValue(":max_storage", max_storage_);
    query.bindValue(":animals_condition", animals_condition_);
    query.bindValue(":feeding_day", feeding_day_);
    query.bindValue(":upgrade_day", upgrade_day_);
    query.bindValue(":is_upgrading", is_upgrading_);
    query.bindValue(":level", level_);
    query.bindValue(":farm_id", farm_id_);
    query.exec();
}

ChickenCoop::ChickenCoop()
{
    type_ = LivingPlace::CHICKEN_COOP;
    storage_ = 0;
    max_storage_ = 0;
    animals_condition_ = AnimalsCondition::HUNGRY;
    feeding_day_ = -1;
    upgrade_day_ = -1;
    is_upgrading_ = false;
    level_ = 0;
}

ChickenCoop &ChickenCoop::get(int chicken_coop_id)
{
    if (chicken_coop == nullptr)
        chicken_coop = new ChickenCoop;

    if (chicken_coop_id != chicken_coop->id_)
    {
        chicken_coop->id_ = chicken_coop_id;
        LivingPlace::get(*chicken_coop, chicken_coop_id);
    }

    return *chicken_coop;
}

ChickenCoop &ChickenCoop::getByFarmId(int farm_id)
{
    if (chicken_coop == nullptr)
        chicken_coop = new ChickenCoop;

    int chicken_coop_id = getLivingPlaceIdByFarmId(farm_id, LivingPlace::CHICKEN_COOP);
    if (chicken_coop_id != chicken_coop->id_)
    {
        chicken_coop->id_ = chicken_coop_id;
        LivingPlace::get(*chicken_coop, chicken_coop_id);
    }

    return *chicken_coop;
}

ChickenCoop &ChickenCoop::create(int farm_id)
{
    if (chicken_coop != nullptr)
        delete chicken_coop;

    chicken_coop = new ChickenCoop;
    id_ = LivingPlace::create(farm_id, LivingPlace::CHICKEN_COOP);
    return *chicken_coop;
}
