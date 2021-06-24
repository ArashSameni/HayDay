#ifndef SILO_H
#define SILO_H

#include <QDateTime>
#include "place.h"

class Silo : Place
{
    static int id_;
    int storage_;
    int max_storage_;
    static Silo* silo;

    Silo();

public:
    Silo(Silo const&) = delete;
    void operator=(Silo const&) = delete;

    static Silo &get(int silo_id);
    static Silo &create();
    static int id(){ return id_; }
    void save();

    //    bool isUpgradable();
    //    int neededNailsToUpgrade();
    //    int neededShovelsToUpgrade();
    //    int neededCoinsToUpgrade();
    //    void upgrade();

    int storage(){ return storage_; }
    int max_storage(){ return max_storage_; }
    void setStorage(int storage){ storage_ = storage; }
    void increaseStorage(int amount){ storage_ += amount; }
    void decreaseStorage(int amount){ storage_ -= amount; }

    ~Silo() { delete silo; }
};

#endif // SILO_H
