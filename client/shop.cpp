#include "shop.h"
#include "livingplaces.h"
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
const int Shop::chicken_sell_coins = 15;

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
const int Shop::sell_xp = 6;


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
    Silo &silo=Farm::get(farmer.farm_id()).silo();

    if (farmer.coins() < wheat_buy_coins)
        return Enums::LACK_OF_COINS;
    if (silo.max_storage() - silo.storage() < count)
        return Enums::LACK_OF_STORAGE;

    return Enums::OK;
}

int Shop::isChickenBuyable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    ChickenCoop &chickenCoop = Farm::get(farmer.farm_id()).chicken_coop();

    if (farmer.coins() < chicken_buy_coins)
        return Enums::LACK_OF_COINS;
    if (chickenCoop.max_storage()-chickenCoop.storage() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_chicken)
        return Enums::LACK_OF_LEVEL;
    if(chickenCoop.animals_condition() == Enums::FED)
        return Enums::FED;
    if(chickenCoop.animals_condition() == Enums::COLLECTABLE)
        return Enums::COLLECTABLE;

    return Enums::OK;
}

int Shop::isCowBuyable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    CowPasture &cowPasture = Farm::get(farmer.farm_id()).cow_pasture();
    if (farmer.coins() < cow_buy_coins)
        return Enums::LACK_OF_COINS;
    if (cowPasture.max_storage() < cowPasture.storage() + count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_cow)
        return Enums::LACK_OF_LEVEL;
    if(cowPasture.animals_condition() == Enums::FED)
        return Enums::FED;
    if(cowPasture.animals_condition() == Enums::COLLECTABLE)
        return Enums::COLLECTABLE;

    return Enums::OK;
}

int Shop::isSheepBuyable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    SheepPasture &sheepPasture = Farm::get(farmer.farm_id()).sheep_pasture();

    if (farmer.coins() < sheep_buy_coins)
        return Enums::LACK_OF_COINS;
    if (sheepPasture.max_storage() < sheepPasture.storage() + count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_sheep)
        return Enums::LACK_OF_LEVEL;
    if(sheepPasture.animals_condition() == Enums::FED)
        return Enums::FED;
    if(sheepPasture.animals_condition() == Enums::COLLECTABLE)
        return Enums::COLLECTABLE;

    return Enums::OK;
}

int Shop::isWheatSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Silo &silo = Farm::get(farmer.farm_id()).silo();

    if (silo.storage() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_wheat)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isAlfalfaSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn = Farm::get(farmer.farm_id()).barn();

    if (barn.alfalfas() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_alfalfa)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isChickenSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    ChickenCoop &chickenCoop = Farm::get(farmer.farm_id()).chicken_coop();

    if (chickenCoop.storage() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_chicken)
        return Enums::LACK_OF_LEVEL;
    if(chickenCoop.animals_condition() == Enums::FED)
        return Enums::FED;
    if(chickenCoop.animals_condition() == Enums::COLLECTABLE)
        return Enums::COLLECTABLE;

    return Enums::OK;
}

int Shop::isEggSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn = Farm::get(farmer.farm_id()).barn();

    if (barn.eggs() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_egg)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isCowSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    CowPasture &cowPasture = Farm::get(farmer.farm_id()).cow_pasture();

    if (cowPasture.storage() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_cow)
        return Enums::LACK_OF_LEVEL;
    if(cowPasture.animals_condition() == Enums::FED)
        return Enums::FED;
    if(cowPasture.animals_condition() == Enums::COLLECTABLE)
        return Enums::COLLECTABLE;

    return Enums::OK;
}

int Shop::isMilkSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn = Farm::get(farmer.farm_id()).barn();

    if (barn.milks() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_milk)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isSheepSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    SheepPasture &sheepPasture = Farm::get(farmer.farm_id()).sheep_pasture();

    if (sheepPasture.storage() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_sheep)
        return Enums::LACK_OF_LEVEL;
    if(sheepPasture.animals_condition() == Enums::FED)
        return Enums::FED;
    if(sheepPasture.animals_condition() == Enums::COLLECTABLE)
        return Enums::COLLECTABLE;

    return Enums::OK;
}

int Shop::isWoolSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn = Farm::get(farmer.farm_id()).barn();

    if (barn.wools() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_wool)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isNailSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn = Farm::get(farmer.farm_id()).barn();

    if (barn.nails() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_nail)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

int Shop::isShovelSellable(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn = Farm::get(farmer.farm_id()).barn();

    if (barn.shovels() < count)
        return Enums::LACK_OF_STORAGE;
    if (farmer.level() < needed_level_for_shovel)
        return Enums::LACK_OF_LEVEL;

    return Enums::OK;
}

bool Shop::isBarnSpaceEnough(int farmer_id, int count) const
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn = Farm::get(farmer.farm_id()).barn();

    return barn.max_storage() - barn.storage() >= count;
}

int Shop::isSellable(int type, int farmer_id, int count)
{
    if(count == 0)
        return Enums::OK;

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
    if(count == 0)
        return Enums::OK;

    switch (type)
    {
    case Enums::WHEAT:
        return isWheatBuyable(farmer_id, count);

    case Enums::CHICKEN:
        return isChickenBuyable(farmer_id, count);

    case Enums::COW:
        return isCowBuyable(farmer_id, count);

    case Enums::SHEEP:
        return isSheepBuyable(farmer_id, count);

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
    Silo &silo = Farm::get(farmer.farm_id()).silo();

    silo.addWheat(count);
    silo.save();

    farmer.removeCoin(count * wheat_buy_coins);
    farmer.save();
}

void Shop::buyAlfalfa(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn=Farm::get(farmer.farm_id()).barn();

    barn.addAlfalfa(count);
    barn.save();

    farmer.removeCoin(count * alfalfa_buy_coins);
    farmer.save();
}

void Shop::buyChicken(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    ChickenCoop &chickenCoop = Farm::get(farmer.farm_id()).chicken_coop();

    chickenCoop.addAnimal(count);
    chickenCoop.save(chickenCoop.id());

    farmer.removeCoin(count * chicken_buy_coins);
    farmer.save();
}

void Shop::buyCow(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    CowPasture &cowPasture = Farm::get(farmer.farm_id()).cow_pasture();

    cowPasture.addAnimal(count);
    cowPasture.save(cowPasture.id());

    farmer.removeCoin(count * cow_buy_coins);
    farmer.save();
}

void Shop::buySheep(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    SheepPasture &sheepPasture = Farm::get(farmer.farm_id()).sheep_pasture();

    sheepPasture.addAnimal(count);
    sheepPasture.save(sheepPasture.id());

    farmer.removeCoin(count * sheep_buy_coins);
    farmer.save();
}

void Shop::buyNail(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn = Farm::get(farmer.farm_id()).barn();

    barn.addNail(count);
    barn.save();

    farmer.removeCoin(count * nail_buy_coins);
    farmer.save();
}

void Shop::buyShovel(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn = Farm::get(farmer.farm_id()).barn();

    barn.addShovel(count);
    barn.save();

    farmer.removeCoin(count * shovel_buy_coins);
    farmer.save();

}

void Shop::sellWheat(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Silo &silo = Farm::get(farmer.farm_id()).silo();

    silo.removeWheat(count);
    silo.save();

    farmer.addCoin(count * wheat_sell_coins);
    farmer.save();
}

void Shop::sellAlfalfa(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn = Farm::get(farmer.farm_id()).barn();

    barn.removeAlfalfa(count);
    barn.save();

    farmer.addCoin(count * alfalfa_sell_coins);
    farmer.save();
}

void Shop::sellChicken(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    ChickenCoop &chickenCoop = Farm::get(farmer.farm_id()).chicken_coop();

    chickenCoop.removeAnimal(count);
    chickenCoop.save(chickenCoop.id());

    farmer.addCoin(count * chicken_sell_coins);
    farmer.save();
}

void Shop::sellCow(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    CowPasture &cowPasture = Farm::get(farmer.farm_id()).cow_pasture();

    cowPasture.removeAnimal(count);
    cowPasture.save(cowPasture.id());

    farmer.addCoin(count * cow_sell_coins);
    farmer.save();
}

void Shop::sellSheep(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    SheepPasture &sheepPasture = Farm::get(farmer.farm_id()).sheep_pasture();

    sheepPasture.removeAnimal(count);
    sheepPasture.save(sheepPasture.id());

    farmer.addCoin(count * sheep_sell_coins);
    farmer.save();
}

void Shop::sellNail(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn = Farm::get(farmer.farm_id()).barn();

    barn.removeNail(count);
    barn.save();

    farmer.addCoin(count * nail_sell_coins);
    farmer.save();
}

void Shop::sellShovel(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn = Farm::get(farmer.farm_id()).barn();

    barn.removeShovel(count);
    barn.save();

    farmer.addCoin(count * shovel_sell_coins);
    farmer.save();
}

void Shop::sellMilk(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn = Farm::get(farmer.farm_id()).barn();

    barn.removeMilk(count);
    barn.save();

    farmer.addCoin(count * milk_sell_coins);
    farmer.save();
}

void Shop::sellEgg(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn = Farm::get(farmer.farm_id()).barn();

    barn.removeEgg(count);
    barn.save();

    farmer.addCoin(count * egg_sell_coins);
    farmer.save();
}

void Shop::sellWool(int farmer_id, int count)
{
    Farmer &farmer = Farmer::get(farmer_id);
    Barn &barn = Farm::get(farmer.farm_id()).barn();

    barn.removeWool(count);
    barn.save();

    farmer.addCoin(count * wool_sell_coins);
    farmer.save();
}
