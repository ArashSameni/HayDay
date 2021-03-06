#ifndef BARN_H
#define BARN_H
#include "enums.h"
#include "place.h"
#include <QVector>

class Milk
{
    int id_ = 0;
    int manufacture_day_ = -1;
    int expiration_day_ = -1;
    int barn_id_;

public:
    Milk(){}
    explicit Milk(int barn_id);

    int id() const { return id_; }
    void setId(int id) { id_ = id; }

    int manufacture_day() const { return manufacture_day_; }
    void setManufactureDay(int day) { manufacture_day_ = day; }

    int expiration_day() const { return expiration_day_; }
    void setExpirationDay(int day) { expiration_day_ = day; }

    int barn_id() const { return barn_id_; }

    void save();
    void remove();

    bool isExpired();
};

class Barn : public Place
{
    static int id_;
    static Barn *barn;

    int storage_;
    int max_storage_;
    int shovels_;
    int nails_;
    int alfalfas_;
    int eggs_;
    int wools_;
    QVector<Milk> milks_;

    Barn();

public:
    Barn(Barn const &) = delete;
    void operator=(Barn const &) = delete;

    static Barn &get(int barn_id);
    static Barn &create();
    static int id() { return id_; }
    void save() const;

    int upgradeXp();
    bool isUpgradeFinished() const;
    void finishUpgrade();
    int isUpgradable(int farm_id) const;
    int neededNailsToUpgrade() const;
    int neededShovelsToUpgrade() const;
    int neededCoinsToUpgrade() const;
    void upgrade(Farmer& farmer, int barn_id);

    int checkMilksExpiration();

    int storage() const { return storage_; }
    int max_storage() const { return max_storage_; }
    int shovels() const { return shovels_; }
    int nails() const { return nails_; }
    int alfalfas() const { return alfalfas_; }
    int eggs() const { return eggs_; }
    int wools() const { return wools_; }
    int milks() const { return milks_.size(); }

    void addShovel(int amount);
    void addNail(int amount);
    void addAlfalfa(int amount);
    void addEgg(int amount);
    void addWool(int amount);
    void addMilk(const Milk &milk);
    void addMilk(int amount);

    void removeShovel(int amount);
    void removeNail(int amount);
    void removeAlfalfa(int amount);
    void removeEgg(int amount);
    void removeWool(int amount);

    void removeMilk(int amount);
    void removeMilk(const Milk &milk);

    ~Barn() {}
};

#endif // BARN_H
