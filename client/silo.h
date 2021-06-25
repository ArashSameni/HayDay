#ifndef SILO_H
#define SILO_H

#include "place.h"

class Silo : Place
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

    ////////////// Not implemented
    bool checkUpgrade() { return false; }
    bool isUpgradable() { return 0; }
    int neededNailsToUpgrade() { return 0; }
    int neededShovelsToUpgrade() { return 0; }
    int neededCoinsToUpgrade() { return 0; }
    void upgrade() {}
    //////////////

    int storage() { return storage_; }
    int max_storage() { return max_storage_; }
    void setStorage(int storage) { storage_ = storage; }
    void addWheat(int amount) { storage_ += amount; }
    void removeWheat(int amount) { storage_ -= amount; }

    ~Silo() {}
};
int Silo::id_ = 0;
Silo *Silo::silo = nullptr;

#endif // SILO_H
