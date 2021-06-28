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
    int area() const { return area_; }
    int planted_area() const { return planted_area_; }
    int plants_condition() const { return plants_condition_; }
    int planting_day() const { return planting_day_; }

    virtual bool checkPlanting() = 0;
    virtual void plant(int) = 0;
    virtual void reap() = 0;

    virtual ~Field() = 0;
};

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
    void save() const;

    ////////////// Not implemented
    bool checkUpgrade() { return false; }
    bool isUpgradable() const { return 0; }
    int neededNailsToUpgrade() const { return 0; }
    int neededShovelsToUpgrade() const { return 0; }
    int neededCoinsToUpgrade() const { return 0; }
    void upgrade() {}

    void plant(int) {}
    void reap() {}
    bool checkPlanting() { return false; }
    //////////////

    ~WheatField() {}
};

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
    void save() const;

    int plowing_condition() const { return plowing_condition_; }
    int plowing_day() const { return plowing_day_; }
    int neededCoinsToPlow() const { return area_ * 5; }

    ////////////// Not implemented
    bool checkUpgrade() { return false; }
    bool isUpgradable() const { return 0; }
    int neededNailsToUpgrade() const { return 0; }
    int neededShovelsToUpgrade() const { return 0; }
    int neededCoinsToUpgrade() const { return 0; }
    void upgrade() {}

    void plant(int) {}
    void reap() {}
    bool checkPlanting() { return false; }

    bool checkPlowing();
    void plow();
    //////////////

    ~AlfalfaField() {}
};

#endif // FIELDS_H
