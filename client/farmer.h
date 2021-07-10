#ifndef FARMER_H
#define FARMER_H

#include <QString>

class Farmer
{
    static int id_;
    static Farmer *farmer;

    QString nickname_;
    int gender_;
    int coins_;
    int level_;
    int xp_;
    int max_xp_;
    uint joining_date_;
    int farm_id_;
    int account_id_;

    Farmer();

public:
    Farmer(Farmer const &) = delete;
    void operator=(Farmer const &) = delete;

    static Farmer &get(int farmer_id);
    static Farmer &getByAccountId(int account_id);
    static Farmer &create(const QString &nickname, int gender_, int account_id, int farm_id);
    static int id() { return id_; }
    void save() const;

    QString nickname() const { return nickname_; }
    void setNickname(const QString &nickname) { nickname_ = nickname; }

    int coins() const { return coins_; }
    int level() const { return level_; }
    int xp() const { return xp_; }
    int max_xp() const { return max_xp_; }
    uint joining_date() const { return joining_date_; }
    int farm_id() const { return farm_id_; }
    int account_id() const { return account_id_; }

    void addCoin(int amount) { coins_ += amount; }
    void removeCoin(int amount) { coins_ -= amount; }
    bool addXpAndIsLevelFinished(int amount)
    {
        xp_ += amount;
        return isLevelFinished();
    }
    bool isLevelFinished() const { return xp_ >= max_xp_; }

    // Not implemented
    void goNextLevel(){}
};

#endif // FARMER_H
