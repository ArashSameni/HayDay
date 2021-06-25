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

    LivingPlace();

public:
    void save(int id) const;

    int storage() const { return storage_; }
    int max_storage() const { return max_storage_; }
    int animals_condition() const { return animals_condition_; }
    int feeding_day() const { return feeding_day_; }
    int farm_id() const { return farm_id_; }
    void addAnimal(int amount) { storage_ += amount; }

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
    bool isUpgradable() const { return 0; }
    int neededNailsToUpgrade() const { return 0; }
    int neededShovelsToUpgrade() const { return 0; }
    int neededCoinsToUpgrade() const { return 0; }
    void upgrade() {}

    bool checkFeeding() { return false; }
    void feed(int) {}
    void collect() {}
    //////////////

    ~ChickenCoop() {}
};
int ChickenCoop::id_ = 0;
ChickenCoop *ChickenCoop::chicken_coop = nullptr;

class CowPasture : public LivingPlace
{
    static int id_;
    static CowPasture *cow_pasture;

    CowPasture();

public:
    CowPasture(CowPasture const &) = delete;
    void operator=(CowPasture const &) = delete;

    static CowPasture &get(int cow_pasture_id);
    static CowPasture &getByFarmId(int farm_id);
    static CowPasture &create(int farm_id);
    static int id() { return id_; }

    ////////////// Not implemented
    bool checkUpgrade() { return false; }
    bool isUpgradable() const { return 0; }
    int neededNailsToUpgrade() const { return 0; }
    int neededShovelsToUpgrade() const { return 0; }
    int neededCoinsToUpgrade() const { return 0; }
    void upgrade() {}

    bool checkFeeding() { return false; }
    void feed(int) {}
    void collect() {}
    //////////////

    ~CowPasture() {}
};
int CowPasture::id_ = 0;
CowPasture *CowPasture::cow_pasture = nullptr;

class SheepPasture : public LivingPlace
{
    static int id_;
    static SheepPasture *sheep_pasture;

    SheepPasture();

public:
    SheepPasture(SheepPasture const &) = delete;
    void operator=(SheepPasture const &) = delete;

    static SheepPasture &get(int sheep_pasture_id);
    static SheepPasture &getByFarmId(int farm_id);
    static SheepPasture &create(int farm_id);
    static int id() { return id_; }

    ////////////// Not implemented
    bool checkUpgrade() { return false; }
    bool isUpgradable() const { return 0; }
    int neededNailsToUpgrade() const { return 0; }
    int neededShovelsToUpgrade() const { return 0; }
    int neededCoinsToUpgrade() const { return 0; }
    void upgrade() {}

    bool checkFeeding() { return false; }
    void feed(int) {}
    void collect() {}
    //////////////

    ~SheepPasture() {}
};
int SheepPasture::id_ = 0;
SheepPasture *SheepPasture::sheep_pasture = nullptr;

#endif // LIVINGPLACES_H
