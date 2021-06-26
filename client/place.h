#ifndef PLACE_H
#define PLACE_H

class Place
{
protected:
    int level_;
    int upgrade_day_;
    bool is_upgrading_;

public:
    int level() const { return level_; }
    int upgrade_day() const { return upgrade_day_; }
    bool is_upgrading() const { return is_upgrading_; }

    virtual bool checkUpgrade() = 0; //check if upgrade is finished, then upgrade the level and the rest
    virtual bool isUpgradable() const = 0;
    virtual int neededNailsToUpgrade() const = 0;
    virtual int neededShovelsToUpgrade() const = 0;
    virtual int neededCoinsToUpgrade() const = 0;
    virtual void upgrade() = 0;

    virtual ~Place() {}
};

#endif // PLACE_H
