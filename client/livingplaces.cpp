#include "livingplaces.h"
#include <QJsonArray>
#include <QJsonDocument>
#include "globals.h"
#include <QDateTime>
#include "barn.h"
#include "silo.h"
#include "farm.h"
#include <QThread>

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
    QString query = "INSERT INTO LivingPlaces(type, farm_id, animals_condition) VALUES(:type, :farm_id, :animals_condition)";
    query.replace(":type", QString::number(type));
    query.replace(":farm_id", QString::number(farm_id));
    query.replace(":animals_condition", QString::number(Enums::HUNGRY));

    socket.write(query);
    return socket.read().toInt();
}

LivingPlace::LivingPlace(uint upgrade_time) : Place(upgrade_time)
{
    storage_ = 0;
    max_storage_ = 0;
    animals_condition_ = Enums::HUNGRY;
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

ChickenCoop::ChickenCoop() : LivingPlace(3)
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

    if (farm_id != chicken_coop->farm_id_)
    {
        int chicken_coop_id = getLivingPlaceIdByFarmId(farm_id, LivingPlace::CHICKEN_COOP);
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

int ChickenCoop::upgradeXp()
{
    return 5;
}

bool ChickenCoop::isUpgradeFinished() const
{
    return CURRENT_DAY - static_cast<uint>(upgrade_day_) >= upgrade_time;
}

void ChickenCoop::finishUpgrade()
{
    if(level_)
        max_storage_ *= 2;
    else
        max_storage_ = 2;

    level_ += 1;
    is_upgrading_ = false;
    save(id_);
}

void ChickenCoop::upgrade(Farmer& farmer, int barn_id)
{
    if (!is_upgrading_)
    {
        Barn& barn = Barn::get(barn_id);
        farmer.removeCoin(neededCoinsToUpgrade());
        farmer.save();

        barn.removeShovel(neededShovelsToUpgrade());
        barn.removeNail(neededNailsToUpgrade());
        barn.save();

        upgrade_day_ = static_cast<int>(CURRENT_DAY);
        is_upgrading_ = true;
        save(id_);
    }
}

int ChickenCoop::isFeedable(int silo_id)
{
    if(storage_ == 0)
        return Enums::NO_ANIMALS;

    Silo& silo = Silo::get(silo_id);
    if(animals_condition_ != Enums::HUNGRY)
        return Enums::ALREADY_FED;
    if(silo.storage() < storage_)
        return Enums::LACK_OF_WHEAT;

    return Enums::OK;
}

int ChickenCoop::feedXp()
{
    return 1;
}

void ChickenCoop::feed(int silo_id)
{
    Silo& silo = Silo::get(silo_id);
    animals_condition_ = Enums::FED;
    feeding_day_ = static_cast<int>(CURRENT_DAY);
    silo.removeWheat(storage_);
    silo.save();
    save(id_);
}

bool ChickenCoop::isCollectTime() const
{
    return CURRENT_DAY - static_cast<uint>(feeding_day_) >= 2;
}

int ChickenCoop::isCollectable(int barn_id)
{
    Barn& barn = Barn::get(barn_id);
    if(barn.max_storage() - barn.storage() < storage_)
        return Enums::LACK_OF_STORAGE;
    
    return Enums::OK;
}

void ChickenCoop::collect(int barn_id)
{
    Barn& barn = Barn::get(barn_id);

    barn.addEgg(storage_);
    barn.save();

    animals_condition_ = Enums::HUNGRY;
    save(id_);
}

int ChickenCoop::collectXp()
{
    return 2;
}

int ChickenCoop::isUpgradable(int farmer_id) const
{
    Farmer& farmer = Farmer::get(farmer_id);
    Barn& barn = Farm::get(farmer.farm_id()).barn();

    if (farmer.coins() < neededCoinsToUpgrade())
        return Enums::LACK_OF_COINS;
    if (barn.nails() < neededNailsToUpgrade())
        return Enums::LACK_OF_NAILS;
    if (barn.shovels() < neededShovelsToUpgrade())
        return Enums::LACK_OF_SHOVELS;
    if ((level_ && farmer.level() < 3) || (!level_ && farmer.level() < 2))
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int ChickenCoop::neededNailsToUpgrade() const
{
    if (level_)
        return 1;

    return 2;
}

int ChickenCoop::neededShovelsToUpgrade() const
{
    return 0;
}

int ChickenCoop::neededCoinsToUpgrade() const
{
    return 10;
}

CowPasture::CowPasture() : LivingPlace(5)
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

    if (farm_id != cow_pasture->farm_id_)
    {
        int cow_pasture_id = getLivingPlaceIdByFarmId(farm_id, LivingPlace::COW_PASTURE);
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

int CowPasture::upgradeXp()
{
    if (level_)
        return 6;

    return 10;
}

bool CowPasture::isUpgradeFinished() const
{
    return CURRENT_DAY - static_cast<uint>(upgrade_day_) >= upgrade_time;
}

void CowPasture::finishUpgrade()
{
    if(level_)
        max_storage_ *= 2;
    else
        max_storage_ = 2;

    level_ += 1;
    is_upgrading_ = false;
    save(id_);
}

int CowPasture::isUpgradable(int farmer_id) const
{
    Farmer& farmer = Farmer::get(farmer_id);
    Barn& barn = Farm::get(farmer.farm_id()).barn();

    if (farmer.coins() < neededCoinsToUpgrade())
        return Enums::LACK_OF_COINS;
    if (barn.nails() < neededNailsToUpgrade())
        return Enums::LACK_OF_NAILS;
    if (barn.shovels() < neededShovelsToUpgrade())
        return Enums::LACK_OF_SHOVELS;
    if ((level_ && farmer.level() < 5) || (!level_ && farmer.level() < 4))
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

void CowPasture::upgrade(Farmer& farmer, int barn_id)
{
    if (!is_upgrading_)
    {
        Barn& barn = Barn::get(barn_id);
        farmer.removeCoin(neededCoinsToUpgrade());
        farmer.save();

        barn.removeShovel(neededShovelsToUpgrade());
        barn.removeNail(neededNailsToUpgrade());
        barn.save();

        upgrade_day_ = static_cast<int>(CURRENT_DAY);
        is_upgrading_ = true;
        save(id_);
    }
}

int CowPasture::neededNailsToUpgrade() const
{
    if (level_)
        return 2;

    return 3;
}

int CowPasture::neededShovelsToUpgrade() const
{
    if (level_)
        return 0;

    return 1;
}

int CowPasture::neededCoinsToUpgrade() const
{
    if (level_)
        return 15;

    return 20;
}

int CowPasture::isFeedable(int barn_id)
{
    if(storage_ == 0)
        return Enums::NO_ANIMALS;

    Barn& barn = Barn::get(barn_id);
    if(animals_condition_ != Enums::HUNGRY)
        return Enums::ALREADY_FED;
    if(barn.alfalfas() < storage_*2)
        return Enums::LACK_OF_ALFALFA;

    return Enums::OK;
}

int CowPasture::feedXp()
{
    return 3;
}

void CowPasture::feed(int barn_id)
{
    Barn& barn = Barn::get(barn_id);
    animals_condition_ = Enums::FED;
    feeding_day_ = static_cast<int>(CURRENT_DAY);
    barn.removeAlfalfa(storage_*2);
    barn.save();
    save(id_);
}

bool CowPasture::isCollectTime() const
{
    return CURRENT_DAY - static_cast<uint>(feeding_day_) >= 3;
}

int CowPasture::isCollectable(int barn_id)
{
    Barn& barn = Barn::get(barn_id);
    if(barn.max_storage() - barn.storage() < storage_)
        return Enums::LACK_OF_STORAGE;
    return Enums::OK;
}

void CowPasture::collect(int barn_id)
{
    Barn& barn = Barn::get(barn_id);
    barn.addMilk(storage_);
    barn.save();
    animals_condition_ = Enums::HUNGRY;
    save(id_);
}

int CowPasture::collectXp()
{
    return 5;
}

SheepPasture::SheepPasture() : LivingPlace(10)
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

    if (farm_id != sheep_pasture->farm_id_)
    {
        int sheep_pasture_id = getLivingPlaceIdByFarmId(farm_id, LivingPlace::SHEEP_PASTURE);
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

int SheepPasture::upgradeXp()
{
    if (level_)
        return 15;

    return 20;
}

bool SheepPasture::isUpgradeFinished() const
{
    return CURRENT_DAY - static_cast<uint>(upgrade_day_) >= upgrade_time;
}

void SheepPasture::finishUpgrade()
{
    if(level_)
        max_storage_ *= 2;
    else
        max_storage_ = 2;

    level_ += 1;
    is_upgrading_ = false;
    save(id_);
}

int SheepPasture::isUpgradable(int farmer_id) const
{
    Farmer& farmer = Farmer::get(farmer_id);
    Barn& barn = Farm::get(farmer.farm_id()).barn();

    if (farmer.coins() < neededCoinsToUpgrade())
        return Enums::LACK_OF_COINS;
    if (barn.nails() < neededNailsToUpgrade())
        return Enums::LACK_OF_NAILS;
    if (barn.shovels() < neededShovelsToUpgrade())
        return Enums::LACK_OF_SHOVELS;
    if ((level_ && farmer.level() < 7) || (!level_ && farmer.level() < 6))
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

void SheepPasture::upgrade(Farmer& farmer, int barn_id)
{
    if (!is_upgrading_)
    {
        Barn& barn = Barn::get(barn_id);
        farmer.removeCoin(neededCoinsToUpgrade());
        farmer.save();

        barn.removeShovel(neededShovelsToUpgrade());
        barn.removeNail(neededNailsToUpgrade());
        barn.save();

        upgrade_day_ = static_cast<int>(CURRENT_DAY);
        is_upgrading_ = true;
        save(id_);
    }
}

int SheepPasture::neededNailsToUpgrade() const
{
    if (level_)
        return 3;

    return 4;
}

int SheepPasture::neededShovelsToUpgrade() const
{
    if (level_)
        return 1;

    return 2;
}

int SheepPasture::neededCoinsToUpgrade() const
{
    return 50;
}

int SheepPasture::isFeedable(int barn_id)
{
    if(storage_ == 0)
        return Enums::NO_ANIMALS;

    Barn& barn = Barn::get(barn_id);
    if(animals_condition_ != Enums::HUNGRY)
        return Enums::ALREADY_FED;
    if(barn.alfalfas() < storage_)
        return Enums::LACK_OF_ALFALFA;

    return Enums::OK;
}

int SheepPasture::feedXp()
{
    return 7;
}

void SheepPasture::feed(int barn_id)
{
    Barn& barn = Barn::get(barn_id);
    animals_condition_ = Enums::FED;
    feeding_day_ = static_cast<int>(CURRENT_DAY);
    barn.removeAlfalfa(storage_);
    barn.save();
    save(id_);
}

bool SheepPasture::isCollectTime() const
{
    return CURRENT_DAY - static_cast<uint>(feeding_day_) >= 10;
}

int SheepPasture::isCollectable(int farmer_id)
{
    Farmer& farmer = Farmer::get(farmer_id);
    Barn& barn = Farm::get(farmer.farm_id()).barn();
    
    if(barn.max_storage() - barn.storage() < storage_)
        return Enums::LACK_OF_STORAGE;

    if(farmer.coins() < storage_)
        return Enums::LACK_OF_COINS;
    
    return Enums::OK;
}

void SheepPasture::collect(int farmer_id)
{
    Farmer& farmer = Farmer::get(farmer_id);
    Barn& barn = Farm::get(farmer.farm_id()).barn();

    barn.addWool(storage_);
    barn.save();

    farmer.removeCoin(storage_);
    farmer.save();

    animals_condition_ = Enums::HUNGRY;
    save(id_);
}

int SheepPasture::collectXp()
{
    return 9;
}
