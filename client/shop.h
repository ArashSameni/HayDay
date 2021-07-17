#ifndef SHOP_H
#define SHOP_H

#include "enums.h"
#include "farmer.h"
#include "farm.h"
#include "silo.h"

class Shop
{
public:
    Shop();
    static const int cow_sell_coins;
    static const int sheep_sell_coins;
    static const int chicken_sell_coins;
    static const int egg_sell_coins;
    static const int wheat_sell_coins;
    static const int alfalfa_sell_coins;
    static const int milk_sell_coins;
    static const int shovel_sell_coins;
    static const int nail_sell_coins;
    static const int wool_sell_coins;

    static const int cow_buy_coins;
    static const int sheep_buy_coins;
    static const int chicken_buy_coins;
    static const int nail_buy_coins;
    static const int shovel_buy_coins;
    static const int wheat_buy_coins;
    static const int alfalfa_buy_coins;

    static const int wheat_xp;
    static const int alfalfa_xp;
    static const int chicken_xp;
    static const int egg_xp;
    static const int cow_xp;
    static const int sheep_xp;
    static const int milk_xp;
    static const int wool_xp;
    static const int nail_xp;
    static const int shovel_xp;
    static const int sell_xp;

    static const int needed_level_for_wheat;
    static const int needed_level_for_alfalfa;
    static const int needed_level_for_chicken;
    static const int needed_level_for_egg;
    static const int needed_level_for_cow;
    static const int needed_level_for_milk;
    static const int needed_level_for_sheep;
    static const int needed_level_for_wool;
    static const int needed_level_for_nail;
    static const int needed_level_for_shovel;

    int isSellable(int type, int farmer_id, int count);
    int isBuyable(int type, int farmer_id, int count);
    void buy(int type, int farmer_id, int count);
    void sell(int type, int farmer_id, int count);

private:
    void buyWheat(int farmer_id,int count);
    void buyAlfalfa(int farmer_id,int count);
    void buyChicken(int farmer_id,int count);
    void buyCow(int farmer_id,int count);
    void buySheep(int farmer_id,int count);
    void buyNail(int farmer_id,int count);
    void buyShovel(int farmer_id,int count);

    void sellWheat(int farmer_id, int count);
    void sellAlfalfa(int farmer_id, int count);
    void sellChicken(int farmer_id, int count);
    void sellCow(int farmer_id, int count);
    void sellSheep(int farmer_id, int count);
    void sellNail(int farmer_id, int count);
    void sellShovel(int farmer_id, int count);
    void sellMilk(int farmer_id, int count);
    void sellEgg(int farmer_id, int count);
    void sellWool(int farmer_id, int count);

    int isWheatSellable(int farmer_id,int count)const;
    int isAlfalfaSellable(int farmer_id,int count)const;
    int isChickenSellable(int farmer_id,int count)const;
    int isEggSellable(int farmer_id,int count)const;
    int isCowSellable(int farmer_id,int count)const;
    int isMilkSellable(int farmer_id,int count)const;
    int isSheepSellable(int farmer_id,int count)const;
    int isWoolSellable(int farmer_id,int count)const;
    int isNailSellable(int farmer_id,int count)const;
    int isShovelSellable(int farmer_id,int count)const;

    int isWheatBuyable(int farmer_id, int count)const;
    int isAlfalfaBuyable(int farmer_id, int count)const;
    int isChickenBuyable(int farmer_id, int count)const;
    int isCowBuyable(int farmer_id, int count)const;
    int isSheepBuyable(int farmer_id, int count)const;
    int isNailBuyable(int farmer_id, int count)const;
    int isShovelBuyable(int farmer_id, int count)const;

};

#endif // SHOP_H
