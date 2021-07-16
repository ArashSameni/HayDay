#ifndef FIELDS_H
#define FIELDS_H
#include "enums.h"
#include "place.h"

class Field : public Place
{
protected:
    int area_;
    int planted_area_;
    int plants_condition_ = Enums::NOT_PLANTED;
    int planting_day_ = -1;

public:
    Field(uint upgrade_time) : Place(upgrade_time) {}

    int area() const { return area_; }
    int planted_area() const { return planted_area_; }
    int plants_condition() const { return plants_condition_; }
    int planting_day() const { return planting_day_; }


    virtual bool checkPlanting() = 0;
    virtual int plantXp()=0;
    virtual int isPlantable(int id, int amount)=0;
    virtual void plant(int id,int amount) = 0;
    virtual int reapXp()=0;
    virtual bool isReapTime()=0;
    virtual int isReapable(int id)=0;
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

    ////////////// Not implemented
    int upgradeXp() ;
    bool isUpgradeFinished() const;
    void finishUpgrade();
    int isUpgradable(int farmer_id=0) const;
    int neededNailsToUpgrade() const;
    int neededShovelsToUpgrade() const;
    int neededCoinsToUpgrade() const;
    void upgrade(Farmer& farmer, int barn_id);

    int plantXp();
    int isPlantable(int silo_id, int amount);
    void plant(int silo_id,int amount);
    int reapXp();
    bool isReapTime();
    int isReapable(int silo_id);
    void reap(int silo_id);
    bool checkPlanting() { return false; }
    //////////////

    ~WheatField() {}
};

class AlfalfaField : public Field
{
    static int id_;
    static AlfalfaField *alfalfa_field;

    int plowing_condition_ = Enums::NOT_PLOWED;
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
    int upgradeXp() ;
    bool isUpgradeFinished() const;
    void finishUpgrade();
    int isUpgradable(int farmer_id=0) const;
    int neededNailsToUpgrade() const;
    int neededShovelsToUpgrade() const;
    int neededCoinsToUpgrade() const;
    void upgrade(Farmer& farmer, int barn_id);

    int plantXp();
    int isPlantable(int barn_id, int amount);
    void plant(int barn_id,int amount);
    int reapXp();
    bool isReapTime();
    int isReapable(int barn_id);
    void reap(int barn_id);
    bool checkPlanting() { return false; }

    int plowXp();
    int isPlowable(int farmer_id);
    void plow();
    bool isPlowingFinished();
    void finishPlowing();
    bool checkPlowing();

    //////////////

    ~AlfalfaField() {}
};

#endif // FIELDS_H
