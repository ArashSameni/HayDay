#ifndef FIELDS_H
#define FIELDS_H

#include "place.h"

enum PlantsCondition
{
    NOT_PLANTED,
    PLANTED,
    REAPABLE
};

class Field
{
protected:
    int area_;
    int planted_area_;
    int plants_condition_ = PlantsCondition::NOT_PLANTED;
    int planting_day_ = -1;

public:
    int area() { return area_; }
    int planted_area() { return planted_area_; }
    int plants_condition() { return plants_condition_; }
    int planting_day() { return planting_day_; }
    virtual bool checkPlanting() { return false; }

    virtual void plant(int) {}
    virtual void reap() {}

    virtual ~Field() = 0;
};
Field::~Field() {}

class WheatField : Field, Place
{
    static int id_;
    static WheatField *wheat_field;

    WheatField();

public:
    WheatField(WheatField const &) = delete;
    void operator=(WheatField const &) = delete;

    static WheatField &get(int wheat_field_id);
    static WheatField &create();
    static int id() { return id_; }
    void save();

    //    bool checkUpgrade(){ return false; }
    //    bool isUpgradable();
    //    int neededNailsToUpgrade();
    //    int neededShovelsToUpgrade();
    //    int neededCoinsToUpgrade();
    //    void upgrade();

    //    void plant(int) {}
    //    void reap() {}
};
int WheatField::id_ = 0;
WheatField *WheatField::wheat_field = nullptr;

#endif // FIELDS_H
