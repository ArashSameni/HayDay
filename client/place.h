#ifndef PLACE_H
#define PLACE_H

#include "farmer.h"

class Place
{
protected:
    int level_;
    int upgrade_day_;
    bool is_upgrading_;

    virtual int neededNailsToUpgrade(int barn_id = 0) const = 0;
    virtual int neededShovelsToUpgrade(int barn_id = 0) const = 0;
    virtual int neededCoinsToUpgrade(int barn_id = 0) const = 0;

public:
    enum
    {
        LACK_OF_COINS,
        LACK_OF_NAILS,
        LACK_OF_SHOVELS,
        LACK_OF_LEVEL,
        OK
    };
    int level() const { return level_; }
    int upgrade_day() const { return upgrade_day_; }
    bool is_upgrading() const { return is_upgrading_; }

    virtual int upgradeXp() = 0;
    virtual bool isUpgradeFinished() const = 0;
    virtual void finishUpgrade() = 0;
    virtual int isUpgradable(int farmer_id) const = 0;
    virtual void upgrade() = 0;

    virtual ~Place() {}
};

#endif // PLACE_H
