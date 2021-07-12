#ifndef LIVINGPLACES_H
#define LIVINGPLACES_H
#include "enums.h"
#include "place.h"


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
    int animals_condition_ = Enums::HUNGRY;
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

    virtual int isFeedable(int) = 0;
    virtual int feedXp() = 0;
    virtual void feed(int) = 0;
    virtual bool isCollectTime() = 0;
    virtual int isCollectable(int) = 0;
    virtual void collect(int) = 0;
    virtual int collectXp() = 0;

    virtual ~LivingPlace() = 0;
};

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

    int upgradeXp();
    bool isUpgradeFinished() const;
    void finishUpgrade();
    int isUpgradable(int farmer_id = 0) const;
    int neededNailsToUpgrade(int barn_id = 0) const;
    int neededShovelsToUpgrade(int barn_id = 0) const;
    int neededCoinsToUpgrade(int barn_id = 0) const;
    void upgrade();

    int isFeedable(int silo_id);
    int feedXp();
    void feed(int silo_id);
    bool isCollectTime();
    int isCollectable(int barn_id);
    void collect(int barn_id);
    int collectXp();

    ~ChickenCoop() {}
};

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

    int upgradeXp();
    bool isUpgradeFinished() const;
    void finishUpgrade();
    int isUpgradable(int farmer_id = 0) const;
    int neededNailsToUpgrade(int barn_id = 0) const;
    int neededShovelsToUpgrade(int barn_id = 0) const;
    int neededCoinsToUpgrade(int barn_id = 0) const;
    void upgrade();
    
    
    int isFeedable(int barn_id);
    int feedXp();
    void feed(int barn_id);
    bool isCollectTime();
    int isCollectable(int barn_id);
    void collect(int barn_id);
    int collectXp();


    ~CowPasture() {}
};

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


    int upgradeXp();
    bool isUpgradeFinished() const;
    void finishUpgrade();
    int isUpgradable(int farmer_id = 0) const;
    int neededNailsToUpgrade(int barn_id = 0) const;
    int neededShovelsToUpgrade(int barn_id = 0) const;
    int neededCoinsToUpgrade(int barn_id = 0) const;
    void upgrade();

    int isFeedable(int barn_id);
    int feedXp();
    void feed(int barn_id);
    bool isCollectTime();
    int isCollectable(int farmer_id);
    void collect(int barn_id);
    int collectXp();

    ~SheepPasture() {}
};

#endif // LIVINGPLACES_H
