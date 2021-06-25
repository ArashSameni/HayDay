#ifndef BARN_H
#define BARN_H

#include "place.h"
#include <QVector>

class Milk
{
    int id_ = 0;
    int manufacture_day_ = -1;
    int expiration_day_ = -1;
    int barn_id_;

public:
    explicit Milk(int barn_id);

    int id() { return id_; }
    void setId(int id) { id_ = id; }

    int manufacture_day() { return manufacture_day_; }
    void setManufactureDay(int day) { manufacture_day_ = day; }

    int expiration_day() { return expiration_day_; }
    void setExpirationDay(int day) { expiration_day_ = day; }

    int barn_id() { return barn_id_; }

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
    void save();

    ////////////// Not implemented
    bool checkUpgrade() { return false; }
    bool isUpgradable() { return 0; }
    int neededNailsToUpgrade() { return 0; }
    int neededShovelsToUpgrade() { return 0; }
    int neededCoinsToUpgrade() { return 0; }
    void upgrade() {}
    //////////////

    void checkMilksExpiration();

    int storage() { return storage_; }
    int max_storage() { return max_storage_; }
    int shovels() { return shovels_; }
    int nails() { return nails_; }
    int alfalfas() { return alfalfas_; }
    int eggs() { return eggs_; }
    int wools() { return wools_; }
    int milks(){ return milks_.size(); }

    void addShovel(int amount);
    void addNail(int amount);
    void addAlfalfa(int amount);
    void addEgg(int amount);
    void addWool(int amount);
    void addMilk(Milk milk);

    void removeShovel(int amount);
    void removeNail(int amount);
    void removeAlfalfa(int amount);
    void removeEgg(int amount);
    void removeWool(int amount);

    void removeMilk(int milk_id);
    void removeMilk(Milk milk);

    ~Barn() {}
};
int Barn::id_ = 0;
Barn *Barn::barn = nullptr;

#endif // BARN_H
