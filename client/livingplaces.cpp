#include "livingplaces.h"
#include <QJsonArray>
#include <QJsonDocument>
#include "globals.h"
#include <QDateTime>

int ChickenCoop::id_ = 0;
ChickenCoop *ChickenCoop::chicken_coop = nullptr;

int CowPasture::id_ = 0;
CowPasture *CowPasture::cow_pasture = nullptr;

int SheepPasture::id_ = 0;
SheepPasture *SheepPasture::sheep_pasture = nullptr;

LivingPlace::~LivingPlace() {}

void LivingPlace::get(LivingPlace &living_place, int living_place_id)
{
    QString query = "SELECT type, storage, max_storage, animals_condition, feeding_day, upgrade_day, is_upgrading, level, farm_id"
                    " FROM LivingPlaces WHERE id=:id";
    query.replace(":id", QString::number(living_place_id));

    socket.write(query);
    QJsonDocument servers_answer = QJsonDocument::fromJson(socket.read());

    if (!servers_answer.isNull())
    {
        QJsonArray data = servers_answer.array()[0].toArray();

        living_place.type_ = data[0].toString().toInt();
        living_place.storage_ = data[1].toString().toInt();
        living_place.max_storage_ = data[2].toString().toInt();
        living_place.animals_condition_ = data[3].toString().toInt();
        living_place.feeding_day_ = data[4].toString().toInt();
        living_place.upgrade_day_ = data[5].toString().toInt();
        living_place.is_upgrading_ = data[6].toString().toInt();
        living_place.level_ = data[7].toString().toInt();
        living_place.farm_id_ = data[8].toString().toInt();
    }
    else
    {
        QString err = "LivingPlace with id " + QString::number(living_place_id) + " doesn't exist!";
        throw err.toStdString().c_str();
    }
}

int LivingPlace::getLivingPlaceIdByFarmId(int farm_id, int type)
{
    QString query = "SELECT id"
                    " FROM LivingPlaces WHERE farm_id=:farm_id AND type=:type";
    query.replace(":farm_id", QString::number(farm_id));
    query.replace(":type", QString::number(type));

    socket.write(query);
    QJsonDocument servers_answer = QJsonDocument::fromJson(socket.read());

    if (!servers_answer.isNull())
    {
        return servers_answer.array()[0].toArray()[0].toString().toInt();
    }
    else
    {
        QString err = "LivingPlace with farmId " + QString::number(farm_id) + " and type " + QString::number(type) + " doesn't exist!";
        throw err.toStdString().c_str();
    }
}

int LivingPlace::create(int farm_id, int type)
{
    QString query = "INSERT INTO LivingPlaces(type, farm_id) VALUES(:type, :farm_id)";
    query.replace(":type", QString::number(type));
    query.replace(":farm_id", QString::number(farm_id));

    socket.write(query);
    return socket.read().toInt();
}

LivingPlace::LivingPlace()
{
    storage_ = 0;
    max_storage_ = 0;
    animals_condition_ = AnimalsCondition::HUNGRY;
    feeding_day_ = -1;
    upgrade_day_ = -1;
    is_upgrading_ = false;
    level_ = 0;
}

void LivingPlace::save(int id) const
{
    QString query = "UPDATE LivingPlaces SET type=:type, storage=:storage, "
                    "max_storage=:max_storage, animals_condition=:animals_condition, "
                    "feeding_day=:feeding_day, upgrade_day=:upgrade_day, is_upgrading=:is_upgrading, "
                    "level=:level, farm_id=:farm_id "
                    "WHERE id=:id";
    query.replace(":id", QString::number(id));
    query.replace(":type", QString::number(type_));
    query.replace(":storage", QString::number(storage_));
    query.replace(":max_storage", QString::number(max_storage_));
    query.replace(":animals_condition", QString::number(animals_condition_));
    query.replace(":feeding_day", QString::number(feeding_day_));
    query.replace(":upgrade_day", QString::number(upgrade_day_));
    query.replace(":is_upgrading", QString::number(is_upgrading_));
    query.replace(":level", QString::number(level_));
    query.replace(":farm_id", QString::number(farm_id_));

    socket.write(query);
}

ChickenCoop::ChickenCoop()
{
    type_ = LivingPlace::CHICKEN_COOP;
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
    chicken_coop->farm_id_ = farm_id;

    id_ = LivingPlace::create(farm_id, LivingPlace::CHICKEN_COOP);
    return *chicken_coop;
}

CowPasture::CowPasture()
{
    type_ = LivingPlace::COW_PASTURE;
}

CowPasture &CowPasture::get(int cow_pasture_id)
{
    if (cow_pasture == nullptr)
        cow_pasture = new CowPasture;

    if (cow_pasture_id != cow_pasture->id_)
    {
        cow_pasture->id_ = cow_pasture_id;
        LivingPlace::get(*cow_pasture, cow_pasture_id);
    }

    return *cow_pasture;
}

CowPasture &CowPasture::getByFarmId(int farm_id)
{
    if (cow_pasture == nullptr)
        cow_pasture = new CowPasture;

    int cow_pasture_id = getLivingPlaceIdByFarmId(farm_id, LivingPlace::COW_PASTURE);
    if (cow_pasture_id != cow_pasture->id_)
    {
        cow_pasture->id_ = cow_pasture_id;
        LivingPlace::get(*cow_pasture, cow_pasture_id);
    }

    return *cow_pasture;
}

CowPasture &CowPasture::create(int farm_id)
{
    if (cow_pasture != nullptr)
        delete cow_pasture;

    cow_pasture = new CowPasture;
    cow_pasture->farm_id_ = farm_id;

    id_ = LivingPlace::create(farm_id, LivingPlace::COW_PASTURE);
    return *cow_pasture;
}

SheepPasture::SheepPasture()
{
    type_ = LivingPlace::SHEEP_PASTURE;
}

SheepPasture &SheepPasture::get(int sheep_pasture_id)
{
    if (sheep_pasture == nullptr)
        sheep_pasture = new SheepPasture;

    if (sheep_pasture_id != sheep_pasture->id_)
    {
        sheep_pasture->id_ = sheep_pasture_id;
        LivingPlace::get(*sheep_pasture, sheep_pasture_id);
    }

    return *sheep_pasture;
}

SheepPasture &SheepPasture::getByFarmId(int farm_id)
{
    if (sheep_pasture == nullptr)
        sheep_pasture = new SheepPasture;

    int sheep_pasture_id = getLivingPlaceIdByFarmId(farm_id, LivingPlace::SHEEP_PASTURE);
    if (sheep_pasture_id != sheep_pasture->id_)
    {
        sheep_pasture->id_ = sheep_pasture_id;
        LivingPlace::get(*sheep_pasture, sheep_pasture_id);
    }

    return *sheep_pasture;
}

SheepPasture &SheepPasture::create(int farm_id)
{
    if (sheep_pasture != nullptr)
        delete sheep_pasture;

    sheep_pasture = new SheepPasture;
    sheep_pasture->farm_id_ = farm_id;

    id_ = LivingPlace::create(farm_id, LivingPlace::SHEEP_PASTURE);
    return *sheep_pasture;
}
