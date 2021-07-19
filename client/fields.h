#ifndef FIELDS_H
#define FIELDS_H
#include "enums.h"
#include "place.h"

class Field : public Place
{
protected:
    int area_;
    int planted_area_;
    int plants_condition_;
    int planting_day_ = -1;

public:
    Field(uint upgrade_time) : Place(upgrade_time) {}

    int area() const { return area_; }
    int planted_area() const { return planted_area_; }
    int plants_condition() const { return plants_condition_; }
    int planting_day() const { return planting_day_; }

    virtual int plantXp() const = 0;
    virtual int isPlantable(int id, int amount) const = 0;
    virtual void plant(int id, int amount) = 0;
    virtual int reapXp() const = 0;
    virtual bool isPlantingFinished() const = 0;
    virtual void finishPlanting() = 0;
    virtual int isReapable(int id) const = 0;
    virtual void reap(int id) = 0;

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

    int upgradeXp();
    bool isUpgradeFinished() const;
    void finishUpgrade();
    int isUpgradable(int farmer_id = 0) const;
    int neededNailsToUpgrade() const;
    int neededShovelsToUpgrade() const;
    int neededCoinsToUpgrade() const;
    void upgrade(Farmer &farmer, int barn_id);

    int plantXp() const;
    int isPlantable(int silo_id, int amount) const;
    void plant(int silo_id, int amount);
    int reapXp() const;
    bool isPlantingFinished() const;
    void finishPlanting();
    int isReapable(int silo_id) const;
    void reap(int silo_id);

    ~WheatField() {}
};

class AlfalfaField : public Field
{
    static int id_;
    static AlfalfaField *alfalfa_field;

    int plowing_day_ = -1;

    AlfalfaField();

public:
    AlfalfaField(AlfalfaField const &) = delete;
    void operator=(AlfalfaField const &) = delete;

    static AlfalfaField &get(int alfalfa_field_id);
    static AlfalfaField &create();
    static int id() { return id_; }
    void save() const;

    int plowing_day() const { return plowing_day_; }

    int upgradeXp();
    bool isUpgradeFinished() const;
    void finishUpgrade();
    int isUpgradable(int farmer_id = 0) const;
    int neededNailsToUpgrade() const;
    int neededShovelsToUpgrade() const;
    int neededCoinsToUpgrade() const;
    void upgrade(Farmer &farmer, int barn_id);

    int plantXp() const;
    int isPlantable(int barn_id, int amount) const;
    void plant(int barn_id, int amount);
    int reapXp() const;
    bool isPlantingFinished() const;
    void finishPlanting();
    int isReapable(int barn_id) const;
    void reap(int barn_id);

    int neededCoinsToPlow() const { return area_ * 5; }
    int plowXp() const;
    int isPlowable(int farmer_id) const;
    void plow(int farmer_id);
    bool isPlowingFinished() const;
    void finishPlowing();

    ~AlfalfaField() {}
};

#endif // FIELDS_H
