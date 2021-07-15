#ifndef SILO_H
#define SILO_H

#include "place.h"

class Silo : public Place
{
    static int id_;
    int storage_;
    int max_storage_;
    static Silo *silo;

    Silo();

public:
    Silo(Silo const &) = delete;
    void operator=(Silo const &) = delete;

    static Silo &get(int silo_id);
    static Silo &create();
    static int id() { return id_; }
    void save();

    int upgradeXp();
    bool isUpgradeFinished() const;
    void finishUpgrade();
    int isUpgradable(int farmer_id) const;
    int neededNailsToUpgrade() const;
    int neededShovelsToUpgrade() const;
    int neededCoinsToUpgrade() const;
    void upgrade();

    int storage() const { return storage_; }
    int max_storage() const { return max_storage_; }
    void setStorage(int storage) { storage_ = storage; }
    void addWheat(int amount) { storage_ += amount; }
    void removeWheat(int amount) { storage_ -= amount; }

    ~Silo() {}
};

#endif // SILO_H
