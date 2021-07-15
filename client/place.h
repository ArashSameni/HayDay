#ifndef PLACE_H
#define PLACE_H
#include "enums.h"
#include "farmer.h"

class Place
{
protected:
    int level_;
    int upgrade_day_;
    bool is_upgrading_;

public:
    const uint upgrade_time;
    Place(uint upgrade_time) : upgrade_time(upgrade_time){}

    int level() const { return level_; }
    int upgrade_day() const { return upgrade_day_; }
    bool is_upgrading() const { return is_upgrading_; }

    virtual int upgradeXp() = 0;
    virtual bool isUpgradeFinished() const = 0;
    virtual void finishUpgrade() = 0;
    virtual int isUpgradable(int farmer_id) const = 0;
    virtual void upgrade() = 0;

    virtual int neededNailsToUpgrade() const = 0;
    virtual int neededShovelsToUpgrade() const = 0;
    virtual int neededCoinsToUpgrade() const = 0;

    virtual ~Place() {}
};

#endif // PLACE_H
