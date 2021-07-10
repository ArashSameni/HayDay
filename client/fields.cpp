#include "fields.h"
#include <QJsonArray>
#include <QJsonDocument>
#include "globals.h"
#include <QDateTime>
#include <string>
#include "farm.h"
#include "barn.h"

int WheatField::id_ = 0;
WheatField *WheatField::wheat_field = nullptr;

int AlfalfaField::id_ = 0;
AlfalfaField *AlfalfaField::alfalfa_field = nullptr;

Field::~Field() {}

WheatField::WheatField()
{
    level_ = 1;
    upgrade_day_ = -1;
    is_upgrading_ = false;
    area_ = 5;
    planted_area_ = 0;
    plants_condition_ = PlantsCondition::NOT_PLANTED;
    planting_day_ = -1;
}

WheatField &WheatField::get(int wheat_field_id)
{
    if (wheat_field == nullptr)
        wheat_field = new WheatField;

    if (wheat_field_id != wheat_field->id_)
    {
        wheat_field->id_ = wheat_field_id;

        QString query = "SELECT area, planted_area, plants_condition, planting_day, upgrade_day, is_upgrading, level"
                        " FROM WheatFields WHERE id=:id";
        query.replace(":id", QString::number(wheat_field_id));

        socket.write(query);
        QJsonDocument servers_answer = QJsonDocument::fromJson(socket.read());

        if (!servers_answer.isNull())
        {
            QJsonArray data = servers_answer.array()[0].toArray();

            wheat_field->area_ = data[0].toString().toInt();
            wheat_field->planted_area_ = data[1].toString().toInt();
            wheat_field->plants_condition_ = data[2].toString().toInt();
            wheat_field->planting_day_ = data[3].toString().toInt();
            wheat_field->upgrade_day_ = data[4].toString().toInt();
            wheat_field->is_upgrading_ = data[5].toString().toInt();
            wheat_field->level_ = data[6].toString().toInt();
        }
        else
        {
            QString err = "WheatField with id " + QString::number(wheat_field_id) + " doesn't exist!";
            throw err.toStdString().c_str();
        }
    }

    return *wheat_field;
}

WheatField &WheatField::create()
{
    if (wheat_field != nullptr)
        delete wheat_field;

    wheat_field = new WheatField;
    QString query = "INSERT INTO WheatFields DEFAULT VALUES";

    socket.write(query);
    id_ = socket.read().toInt();

    return *wheat_field;
}

void WheatField::save() const
{
    QString query = "UPDATE WheatFields SET area=:area, planted_area=:planted_area, "
                    "plants_condition=:plants_condition, planting_day=:planting_day, "
                    "upgrade_day=:upgrade_day, is_upgrading=:is_upgrading, level=:level "
                    "WHERE id=:id";
    query.replace(":id", QString::number(id_));
    query.replace(":area", QString::number(area_));
    query.replace(":planted_area", QString::number(planted_area_));
    query.replace(":plants_condition", QString::number(plants_condition_));
    query.replace(":planting_day", QString::number(planting_day_));
    query.replace(":upgrade_day", QString::number(upgrade_day_));
    query.replace(":is_upgrading", QString::number(is_upgrading_));
    query.replace(":level", QString::number(level_));

    socket.write(query);
}

int WheatField::upgradeXp()
{
    return 3;
}

bool WheatField::isUpgradeFinished() const
{
    return CURRENT_DAY - static_cast<uint>(upgrade_day_) >= 2;
}

void WheatField::finishUpgrade()
{
    level_ += 1;
    area_ *= 2;
    is_upgrading_ = false;
    save();
}

int WheatField::isUpgradable(int farmer_id) const
{
    Farmer& farmer = Farmer::get(farmer_id);
    Barn& barn = Farm::get(farmer.farm_id()).barn();

    if (farmer.coins() < neededCoinsToUpgrade())
        return LACK_OF_COINS;
    if (barn.nails() < neededNailsToUpgrade())
        return LACK_OF_NAILS;
    if (barn.shovels() < neededShovelsToUpgrade())
        return LACK_OF_SHOVELS;
    if (farmer.level() < 2)
        return LACK_OF_LEVEL;

    return OK;
}

void WheatField::upgrade()
{
    if (!is_upgrading_)
    {
        upgrade_day_ = static_cast<int>(CURRENT_DAY);
        is_upgrading_ = true;
        save();
    }
}

int WheatField::neededNailsToUpgrade(int) const
{
    return 0;
}

int WheatField::neededShovelsToUpgrade(int) const
{
    return 1;
}

int WheatField::neededCoinsToUpgrade(int) const
{
    return 5;
}

AlfalfaField::AlfalfaField()
{
    level_ = 0;
    upgrade_day_ = -1;
    is_upgrading_ = false;
    area_ = 0;
    planted_area_ = 0;
    plants_condition_ = PlantsCondition::NOT_PLANTED;
    planting_day_ = -1;
    plowing_condition_ = PlowingCondition::NOT_PLOWED;
    plowing_day_ = -1;
}

AlfalfaField &AlfalfaField::get(int alfalfa_field_id)
{
    if (alfalfa_field == nullptr)
        alfalfa_field = new AlfalfaField;

    if (alfalfa_field_id != alfalfa_field->id_)
    {
        alfalfa_field->id_ = alfalfa_field_id;

        QString query = "SELECT area, planted_area, plants_condition, planting_day, upgrade_day, is_upgrading, level"
                        ", plowing_condition, plowing_day"
                        " FROM AlfalfaFields WHERE id=:id";
        query.replace(":id", QString::number(alfalfa_field_id));

        socket.write(query);
        QJsonDocument servers_answer = QJsonDocument::fromJson(socket.read());

        if (!servers_answer.isNull())
        {
            QJsonArray data = servers_answer.array()[0].toArray();

            alfalfa_field->area_ = data[0].toString().toInt();
            alfalfa_field->planted_area_ = data[1].toString().toInt();
            alfalfa_field->plants_condition_ = data[2].toString().toInt();
            alfalfa_field->planting_day_ = data[3].toString().toInt();
            alfalfa_field->upgrade_day_ = data[4].toString().toInt();
            alfalfa_field->is_upgrading_ = data[5].toString().toInt();
            alfalfa_field->level_ = data[6].toString().toInt();
            alfalfa_field->plowing_condition_ = data[7].toString().toInt();
            alfalfa_field->plowing_day_ = data[8].toString().toInt();
        }
        else
        {
            QString err = "AlfalfaField with id " + QString::number(alfalfa_field_id) + " doesn't exist!";
            throw err.toStdString().c_str();
        }
    }

    return *alfalfa_field;
}

AlfalfaField &AlfalfaField::create()
{
    if (alfalfa_field != nullptr)
        delete alfalfa_field;

    alfalfa_field = new AlfalfaField;
    QString query = "INSERT INTO AlfalfaFields DEFAULT VALUES";

    socket.write(query);
    id_ = socket.read().toInt();

    return *alfalfa_field;
}

void AlfalfaField::save() const
{
    QString query = "UPDATE AlfalfaFields SET area=:area, planted_area=:planted_area, "
                    "plants_condition=:plants_condition, planting_day=:planting_day, "
                    "upgrade_day=:upgrade_day, is_upgrading=:is_upgrading, level=:level "
                    "plowing_condition=:plowing_condition, plowing_day=:plowing_day "
                    "WHERE id=:id";
    query.replace(":id", QString::number(id_));
    query.replace(":area", QString::number(area_));
    query.replace(":planted_area", QString::number(planted_area_));
    query.replace(":plants_condition", QString::number(plants_condition_));
    query.replace(":planting_day", QString::number(planting_day_));
    query.replace(":upgrade_day", QString::number(upgrade_day_));
    query.replace(":is_upgrading", QString::number(is_upgrading_));
    query.replace(":level", QString::number(level_));
    query.replace(":plowing_condition", QString::number(plowing_condition_));
    query.replace(":plowing_day", QString::number(plowing_day_));

    socket.write(query);
}

int AlfalfaField::upgradeXp()
{
    if (level_)
        return 3;
    return 6;
}

bool AlfalfaField::isUpgradeFinished() const
{
    return CURRENT_DAY - static_cast<uint>(upgrade_day_) >= 3;
}

void AlfalfaField::finishUpgrade()
{
    if (level_)
        area_ *= 2;
    else
        area_ = 4;

    level_ += 1;
    is_upgrading_ = false;
    save();
}

int AlfalfaField::isUpgradable(int farmer_id) const
{
    Farmer& farmer = Farmer::get(farmer_id);
    Barn& barn = Farm::get(farmer.farm_id()).barn();

    if (farmer.coins() < neededCoinsToUpgrade())
        return LACK_OF_COINS;
    if (barn.nails() < neededNailsToUpgrade())
        return LACK_OF_NAILS;
    if (barn.shovels() < neededShovelsToUpgrade())
        return LACK_OF_SHOVELS;
    if ((level_ && farmer.level() < 4) || (!level_ && farmer.level() < 3))
        return LACK_OF_LEVEL;

    return OK;
}

void AlfalfaField::upgrade()
{
    if (!is_upgrading_)
    {
        upgrade_day_ = static_cast<int>(CURRENT_DAY);
        is_upgrading_ = true;
        save();
    }
}

int AlfalfaField::neededNailsToUpgrade(int) const
{
    if (level_)
        return 0;

    return 1;
}

int AlfalfaField::neededShovelsToUpgrade(int) const
{
    if (level_)
        return 2;

    return 1;
}

int AlfalfaField::neededCoinsToUpgrade(int) const
{
    if (level_)
        return 5;

    return 15;
}
