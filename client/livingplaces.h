#ifndef LIVINGPLACES_H
#define LIVINGPLACES_H

#include "place.h"

enum AnimalsCondition
{
    HUNGRY,
    FED,
    COLLECTABLE
};

class LivingPlace : public Place
{
public:
    enum
    {
        CHICKEN_COOP,
        COW_PASTURE,
        SHEEP_PASTURE
    };

protected:
    int type_;
    int storage_;
    int max_storage_;
    int animals_condition_ = AnimalsCondition::HUNGRY;
    int feeding_day_ = -1;
    int farm_id_;

    static void get(LivingPlace &living_place, int living_place_id);
    static int getLivingPlaceIdByFarmId(int farm_id, int type);
    static int create(int farm_id, int type);

public:
    void save(int id);

    int storage() { return storage_; }
    int max_storage() { return max_storage_; }
    int animals_condition() { return animals_condition_; }
    int feeding_day() { return feeding_day_; }
    int farm_id() { return farm_id_; }
    void addAnimal(int amount){ storage_ += amount; }

    virtual bool checkFeeding() = 0;
    virtual void feed(int) = 0;
    virtual void collect() = 0;

    virtual ~LivingPlace() = 0;
};
LivingPlace::~LivingPlace() {}

class ChickenCoop : public LivingPlace
{
    static int id_;
    static ChickenCoop *chicken_coop;

    ChickenCoop();

public:
    ChickenCoop(ChickenCoop const &) = delete;
    void operator=(ChickenCoop const &) = delete;

    static ChickenCoop &get(int chicken_coop_id);
    static ChickenCoop &getByFarmId(int farm_id);
    static ChickenCoop &create(int farm_id);
    static int id() { return id_; }

    ////////////// Not implemented
    bool checkUpgrade() { return false; }
    bool isUpgradable() { return 0; }
    int neededNailsToUpgrade() { return 0; }
    int neededShovelsToUpgrade() { return 0; }
    int neededCoinsToUpgrade() { return 0; }
    void upgrade() {}

    bool checkFeeding(){return false;}
    void feed(int){}
    void collect(){}
    //////////////

    ~ChickenCoop() {}
};
int ChickenCoop::id_ = 0;
ChickenCoop *ChickenCoop::chicken_coop = nullptr;

#endif // LIVINGPLACES_H
