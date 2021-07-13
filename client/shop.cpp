#include "shop.h"

Shop::Shop()
{
}
const int Shop::cow_sell_coins = 50;
const int Shop::sheep_sell_coins = 70;
const int Shop::wheat_sell_coins = 2;
const int Shop::alfalfa_sell_coins = 4;
const int Shop::egg_sell_coins = 8;
const int Shop::milk_sell_coins = 12;
const int Shop::wool_sell_coins = 23;
const int Shop::nail_sell_coins = 20;
const int Shop::shovel_sell_coins = 30;

const int Shop::wheat_buy_coins = 3;
const int Shop::alfalfa_buy_coins = 6;
const int Shop::chicken_buy_coins = 20;
const int Shop::cow_buy_coins = 70;
const int Shop::sheep_buy_coins = 80;
const int Shop::nail_buy_coins = 30;
const int Shop::shovel_buy_coins = 50;

const int Shop::wheat_xp = 1;
const int Shop::alfalfa_xp = 2;
const int Shop::chicken_xp = 5;
const int Shop::egg_xp = 3;
const int Shop::cow_xp = 10;
const int Shop::milk_xp = 5;
const int Shop::sheep_xp = 15;
const int Shop::wool_xp = 10;
const int Shop::nail_xp = 4;
const int Shop::shovel_xp = 8;

const int Shop::needed_level_for_wheat = 1;
const int Shop::needed_level_for_alfalfa = 3;
const int Shop::needed_level_for_chicken = 2;
const int Shop::needed_level_for_egg = 2;
const int Shop::needed_level_for_cow = 4;
const int Shop::needed_level_for_milk = 4;
const int Shop::needed_level_for_sheep = 6;
const int Shop::needed_level_for_wool = 6;
const int Shop::needed_level_for_nail = 1;
const int Shop::needed_level_for_shovel = 1;

int Shop::isWheatBuyable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());
    if (farmer.coins() < wheat_buy_coins)
        return Enums::LACK_OF_COINS;
    if (farm.silo().max_storage() < (farm.silo().storage() + count))
        return Enums::LACK_OF_STORAGE;

    return Enums::OK;
}

int Shop::isAlfalfaBuyable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());
    if (farmer.coins() < alfalfa_buy_coins)
        return Enums::LACK_OF_COINS;
    if (farm.barn().max_storage() < (farm.barn().storage() + count))
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_alfalfa)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isChickenBuyable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());
    if (farmer.coins() < chicken_buy_coins)
        return Enums::LACK_OF_COINS;
    if (farm.chicken_coop().max_storage() < (farm.chicken_coop().storage() + count))
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_chicken)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isCowBuyable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());
    if (farmer.coins() < cow_buy_coins)
        return Enums::LACK_OF_COINS;
    if (farm.cow_pasure().max_storage() < (farm.cow_pasure().storage() + count))
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_cow)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isSheepBuyable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());
    if (farmer.coins() < sheep_buy_coins)
        return Enums::LACK_OF_COINS;
    if (farm.sheep_pasture().max_storage() < (farm.sheep_pasture().storage() + count))
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_sheep)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isNailBuyable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());
    if (farmer.coins() < nail_buy_coins)
        return Enums::LACK_OF_COINS;
    if (farm.barn().max_storage() < (farm.barn().storage() + count))
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_nail)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isShovelBuyable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());
    if (farmer.coins() < shovel_buy_coins)
        return Enums::LACK_OF_COINS;
    if (farm.barn().max_storage() < (farm.barn().storage() + count))
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_shovel)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isWheatSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    if (farm.silo().storage() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_wheat)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isAlfalfaSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    if (farm.barn().alfalfas() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_alfalfa)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isChickenSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    if (farm.chicken_coop().storage() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_chicken)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isEggSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    if (farm.barn().eggs() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_egg)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isCowSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    if (farm.cow_pasure().storage() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_cow)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isMilkSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    if (farm.barn().milks() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_milk)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isSheepSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    if (farm.sheep_pasture().storage() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_sheep)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isWoolSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    if (farm.barn().wools() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_wool)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isNailSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    if (farm.barn().nails() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_nail)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isShovelSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    if (farm.barn().shovels() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_shovel)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isSellable(int type, int farmer_id, int count)
{
    switch (type)
    {
    case Enums::WHEAT:
        return isWheatSellable(farmer_id, count);

    case Enums::ALFALFA:
        return isAlfalfaSellable(farmer_id, count);

    case Enums::CHICKEN:
        return isChickenSellable(farmer_id, count);

    case Enums::EGG:
        return isEggSellable(farmer_id, count);

    case Enums::COW:
        return isCowSellable(farmer_id, count);

    case Enums::MILK:
        return isMilkSellable(farmer_id, count);

    case Enums::SHEEP:
        return isSheepSellable(farmer_id, count);

    case Enums::WOOL:
        return isWoolSellable(farmer_id, count);

    case Enums::NAIL:
        return isNailSellable(farmer_id, count);

    case Enums::SHOVEL:
        return isShovelSellable(farmer_id, count);

    default:
        return -1;
    }
}

int Shop::isBuyable(int type, int farmer_id, int count)
{
    switch (type)
    {
    case Enums::WHEAT:
        return isWheatBuyable(farmer_id, count);

    case Enums::ALFALFA:
        return isAlfalfaBuyable(farmer_id, count);

    case Enums::CHICKEN:
        return isChickenBuyable(farmer_id, count);

    case Enums::COW:
        return isCowBuyable(farmer_id, count);

    case Enums::SHEEP:
        return isSheepBuyable(farmer_id, count);

    case Enums::NAIL:
        return isNailBuyable(farmer_id, count);

    case Enums::SHOVEL:
        return isShovelBuyable(farmer_id, count);

    default:
        return -1;
    }
}

void Shop::buy(int type, int farmer_id, int count)
{
    switch (type)
    {
    case Enums::WHEAT:
        buyWheat(farmer_id, count);
        break;

    case Enums::ALFALFA:
        buyAlfalfa(farmer_id, count);
        break;

    case Enums::CHICKEN:
        buyChicken(farmer_id, count);
        break;

    case Enums::COW:
        buyCow(farmer_id, count);
        break;

    case Enums::SHEEP:
        buySheep(farmer_id, count);
        break;

    case Enums::NAIL:
        buyNail(farmer_id, count);
        break;

    case Enums::SHOVEL:
        buyShovel(farmer_id, count);
        break;
    }
}

void Shop::sell(int type, int farmer_id, int count)
{
    switch (type)
    {
    case Enums::WHEAT:
        sellWheat(farmer_id, count);
        break;

    case Enums::EGG:
        sellEgg(farmer_id, count);
        break;

    case Enums::WOOL:
        sellWool(farmer_id, count);
        break;

    case Enums::MILK:
        sellMilk(farmer_id, count);
        break;

    case Enums::ALFALFA:
        sellAlfalfa(farmer_id, count);
        break;

    case Enums::CHICKEN:
        sellChicken(farmer_id, count);
        break;

    case Enums::COW:
        sellCow(farmer_id, count);
        break;

    case Enums::SHEEP:
        sellSheep(farmer_id, count);
        break;

    case Enums::NAIL:
        sellNail(farmer_id, count);
        break;

    case Enums::SHOVEL:
        sellShovel(farmer_id, count);
        break;
    }
}

void Shop::buyWheat(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.silo().addWheat(count);

    farmer.removeCoin(count * wheat_buy_coins);
}

void Shop::buyAlfalfa(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.barn().addAlfalfa(count);

    farmer.removeCoin(count * alfalfa_buy_coins);
}

void Shop::buyChicken(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.chicken_coop().addAnimal(count);

    farmer.removeCoin(count * chicken_buy_coins);
}

void Shop::buyCow(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.cow_pasure().addAnimal(count);

    farmer.removeCoin(count * cow_buy_coins);
}

void Shop::buySheep(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.sheep_pasture().addAnimal(count);

    farmer.removeCoin(count * sheep_buy_coins);
}

void Shop::buyNail(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.barn().addNail(count);

    farmer.removeCoin(count * nail_buy_coins);
}

void Shop::buyShovel(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.barn().addShovel(count);

    farmer.removeCoin(count * shovel_buy_coins);
}

void Shop::sellWheat(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.silo().removeWheat(count);

    farmer.addCoin(count * wheat_sell_coins);
}

void Shop::sellAlfalfa(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.barn().removeAlfalfa(count);

    farmer.addCoin(count * alfalfa_sell_coins);
}

void Shop::sellChicken(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.chicken_coop().removeAnimal(count);

    farmer.addCoin(count * chicken_sell_coins);
}

void Shop::sellCow(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.chicken_coop().removeAnimal(count);

    farmer.addCoin(count * cow_sell_coins);
}

void Shop::sellSheep(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.sheep_pasture().removeAnimal(count);

    farmer.addCoin(count * sheep_sell_coins);
}

void Shop::sellNail(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.barn().addNail(count);

    farmer.addCoin(count * nail_sell_coins);
}

void Shop::sellShovel(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.barn().addShovel(count);

    farmer.addCoin(count * shovel_sell_coins);
}

void Shop::sellMilk(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.barn().addMilk(count);

    farmer.addCoin(count * milk_sell_coins);
}

void Shop::sellEgg(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.barn().addEgg(count);

    farmer.addCoin(count * egg_sell_coins);
}

void Shop::sellWool(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Farm &farm = Farm::get(farmer.farm_id());

    farm.barn().addWool(count);

    farmer.addCoin(count * wool_sell_coins);
}
