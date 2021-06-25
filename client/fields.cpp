#include "fields.h"
#include <QSqlQuery>
#include <QVariant>
#include <string>
#include <exception>

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

        QSqlQuery query;
        query.prepare("SELECT area, planted_area, plants_condition, planting_day, upgrade_day, is_upgrading, level"
                      " FROM WheatFields WHERE id=:id");
        query.bindValue(":id", wheat_field_id);
        query.exec();

        if (query.first())
        {
            wheat_field->area_ = query.value(0).toInt();
            wheat_field->planted_area_ = query.value(1).toInt();
            wheat_field->plants_condition_ = query.value(2).toInt();
            wheat_field->planting_day_ = query.value(3).toInt();
            wheat_field->upgrade_day_ = query.value(4).toInt();
            wheat_field->is_upgrading_ = query.value(5).toInt();
            wheat_field->level_ = query.value(6).toInt();
        }
        else
        {
            std::string err = "WheatField with id " + std::to_string(wheat_field_id) + " doesn't exist!";
            throw std::exception(err.c_str());
        }
    }

    return *wheat_field;
}

WheatField &WheatField::create()
{
    if (wheat_field != nullptr)
        delete wheat_field;

    wheat_field = new WheatField;
    QSqlQuery query;
    query.prepare("INSERT INTO WheatFields DEFAULT VALUES");
    query.exec();

    id_ = query.lastInsertId().toInt();
    return *wheat_field;
}

void WheatField::save()
{
    QSqlQuery query;
    query.prepare("UPDATE WheatFields SET area=:area, planted_area=:planted_area, "
                  "plants_condition=:plants_condition, planting_day=:planting_day, "
                  "upgrade_day=:upgrade_day, is_upgrading=:is_upgrading, level=:level "
                  "WHERE id=:id");
    query.bindValue(":id", id_);
    query.bindValue(":area", area_);
    query.bindValue(":planted_area", planted_area_);
    query.bindValue(":plants_condition", plants_condition_);
    query.bindValue(":planting_day", planting_day_);
    query.bindValue(":upgrade_day", upgrade_day_);
    query.bindValue(":is_upgrading", is_upgrading_);
    query.bindValue(":level", level_);
    query.exec();
}
