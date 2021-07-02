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
    void operator=(Barn const &) = delete;

    static Barn &get(int barn_id);
    static Barn &create();
    static int id() { return id_; }
    void save() const;

    ////////////// Not implemented
    bool checkUpgrade() { return false; }
    bool isUpgradable() const { return 0; }
    int neededNailsToUpgrade() const { return 0; }
    int neededShovelsToUpgrade() const { return 0; }
    int neededCoinsToUpgrade() const { return 0; }
    void upgrade() {}
    //////////////

    void checkMilksExpiration();

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

    void removeShovel(int amount);
    void removeNail(int amount);
    void removeAlfalfa(int amount);
    void removeEgg(int amount);
    void removeWool(int amount);

    void removeMilk(int milk_id);
    void removeMilk(const Milk &milk);

    ~Barn() {}
};

#endif // BARN_H
