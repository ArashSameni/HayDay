#ifndef PLACE_H
#define PLACE_H

class Place
{
protected:
    int level_;
    int upgrade_day_;
    bool is_upgrading_;

public:
    int level() { return level_; }
    int upgrade_day() { return upgrade_day_; }
    bool is_upgrading() { return is_upgrading_; }

    virtual bool checkUpgrade() = 0; //check if upgrade is finished, then upgrade the level and the rest
    virtual bool isUpgradable() = 0;
    virtual int neededNailsToUpgrade() = 0;
    virtual int neededShovelsToUpgrade() = 0;
    virtual int neededCoinsToUpgrade() = 0;
    virtual void upgrade() = 0;

    virtual ~Place() {}
};

#endif // PLACE_H
