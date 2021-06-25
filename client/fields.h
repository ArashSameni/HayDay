#ifndef FIELDS_H
#define FIELDS_H

#include "place.h"

enum PlantsCondition
{
    NOT_PLANTED,
    PLANTED,
    REAPABLE
};

enum PlowingCondition
{
    NOT_PLOWED,
    PLOWING,
    PLOWED
};

class Field : public Place
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

    virtual bool checkPlanting() = 0;
    virtual void plant(int) = 0;
    virtual void reap() = 0;

    virtual ~Field() = 0;
};
Field::~Field() {}

class WheatField : public Field
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

    ////////////// Not implemented
    bool checkUpgrade() { return false; }
    bool isUpgradable() { return 0; }
    int neededNailsToUpgrade() { return 0; }
    int neededShovelsToUpgrade() { return 0; }
    int neededCoinsToUpgrade() { return 0; }
    void upgrade() {}

    void plant(int) {}
    void reap() {}
    bool checkPlanting() { return false; }
    //////////////

    ~WheatField() {}
};
int WheatField::id_ = 0;
WheatField *WheatField::wheat_field = nullptr;

class AlfalfaField : public Field
{
    static int id_;
    static AlfalfaField *alfalfa_field;

    int plowing_condition_ = PlowingCondition::NOT_PLOWED;
    int plowing_day_ = -1;

    AlfalfaField();

public:
    AlfalfaField(AlfalfaField const &) = delete;
    void operator=(AlfalfaField const &) = delete;

    static AlfalfaField &get(int alfalfa_field_id);
    static AlfalfaField &create();
    static int id() { return id_; }
    void save();

    int plowing_condition() { return plowing_condition_; }
    int plowing_day() { return plowing_day_; }
    int neededCoinsToPlow() { return area_ * 5; }

    ////////////// Not implemented
    bool checkUpgrade() { return false; }
    bool isUpgradable() { return 0; }
    int neededNailsToUpgrade() { return 0; }
    int neededShovelsToUpgrade() { return 0; }
    int neededCoinsToUpgrade() { return 0; }
    void upgrade() {}

    void plant(int) {}
    void reap() {}
    bool checkPlanting() { return false; }

    bool checkPlowing();
    void plow();
    //////////////

    ~AlfalfaField() {}
};
int AlfalfaField::id_ = 0;
AlfalfaField *AlfalfaField::alfalfa_field = nullptr;

#endif // FIELDS_H
