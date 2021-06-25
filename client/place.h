#ifndef PLACE_H
#define PLACE_H

class Place
{
protected:
    int level_;
    int upgrade_day_;
    bool is_upgrading_;

public:
    int level(){ return level_; }
    int upgrade_day(){ return upgrade_day_; }
    bool is_upgrading(){ return is_upgrading_; }

    virtual bool checkUpgrade(){ return false; } //check if upgrade is finished, then upgrade the level and the rest
    virtual bool isUpgradable(){ return false; }
    virtual int neededNailsToUpgrade(){ return 0; }
    virtual int neededShovelsToUpgrade(){ return 0; }
    virtual int neededCoinsToUpgrade(){ return 0; }
    virtual void upgrade() {}

    virtual ~Place() = 0;
};

Place::~Place() {}

#endif // PLACE_H
