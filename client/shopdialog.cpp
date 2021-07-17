#include "shopdialog.h"
#include "ui_shopdialog.h"
#include "levelupdialog.h"
#include "messagedialog.h"
#include <QDebug>

ShopDialog::ShopDialog(Farmer& farmer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShopDialog),
    farmer(farmer)
{
    ui->setupUi(this);
    this->setWindowTitle("Shop");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    checkLock();
}

ShopDialog::~ShopDialog()
{
    delete ui;
}

void ShopDialog::showAmount()
{
    showBuyButton();
    showSellButton();
}

void ShopDialog::showBuyButton()
{
    if(buyAmount)
        ui->btnBuy->setText("Buy - " + QString::number(buyAmount));
    else
        ui->btnBuy->setText("Buy");
}

void ShopDialog::showSellButton()
{
    if(sellAmount)
        ui->btnSell->setText("Sell + " + QString::number(sellAmount));
    else
        ui->btnSell->setText("Sell");
}

void ShopDialog::openLockAlfalfa()
{
    delete ui->alfalfaLock;

    ui->btnAlfalfaPlus->setEnabled(true);
    ui->btnAlfalfaMinus->setEnabled(true);
}

void ShopDialog::buy()
{
    QString err;
    bool show_error = true;

    if(shop.isBuyable(Enums::WHEAT, farmer.id(), wheatCount())!= Enums::OK)
        err = getNotEnoughError(Enums::WHEAT, "space");
    else if(shop.isBuyable(Enums::ALFALFA, farmer.id(), alfalfaCount())!= Enums::OK)
        err = getNotEnoughError(Enums::ALFALFA, "space");
    else if(shop.isBuyable(Enums::CHICKEN, farmer.id(), chickenCount())!= Enums::OK)
        err = getNotEnoughError(Enums::CHICKEN, " space");
    else if(shop.isBuyable(Enums::COW, farmer.id(), cowcount())!= Enums::OK)
        err = getNotEnoughError(Enums::COW, "space");
    else if(shop.isBuyable(Enums::SHEEP, farmer.id(), sheepCount())!= Enums::OK)
        err = getNotEnoughError(Enums::SHEEP, "space");
    else if(shop.isBuyable(Enums::NAIL, farmer.id(), nailCount())!= Enums::OK)
        err = getNotEnoughError(Enums::NAIL, "space");
    else if(shop.isBuyable(Enums::SHOVEL, farmer.id(), shovelCount())!= Enums::OK)
        err = getNotEnoughError(Enums::SHOVEL, "space");
    else
    {
        int xp_to_add = 0;
        shop.buy(Enums::WHEAT, farmer.id(), wheatCount());
        xp_to_add += wheatCount() * Shop::wheat_xp;

        shop.buy(Enums::ALFALFA, farmer.id(), alfalfaCount());
        xp_to_add += alfalfaCount() * Shop::alfalfa_xp;

        shop.buy(Enums::CHICKEN, farmer.id(), chickenCount());
        xp_to_add += chickenCount() * Shop::chicken_xp;

        shop.buy(Enums::COW, farmer.id(), cowcount());
        xp_to_add += cowcount() * Shop::cow_xp;

        shop.buy(Enums::SHEEP, farmer.id(), sheepCount());
        xp_to_add += sheepCount() * Shop::sheep_xp;

        shop.buy(Enums::NAIL, farmer.id(), nailCount());
        xp_to_add += nailCount() * Shop::nail_xp;

        shop.buy(Enums::SHOVEL, farmer.id(), shovelCount());
        xp_to_add += shovelCount() * Shop::shovel_xp;

        emit ShowCoin();
        MessageDialog w("The purchase operation was successful!", "Info", this);
        w.exec();

        emit AddXP(xp_to_add);
        show_error = false;
    }

    if(show_error)
    {
        MessageDialog dialog(err, "Error", this);
        dialog.exec();
    }
}

void ShopDialog::sell()
{
    QString err;
    bool show_error = true;

    if(shop.isSellable(Enums::WHEAT, farmer.id(), wheatCount()) != Enums::OK)
        err = getNotEnoughError(Enums::WHEAT, "storage");
    else if(shop.isSellable(Enums::ALFALFA, farmer.id(), alfalfaCount())!= Enums::OK)
        err = getNotEnoughError(Enums::ALFALFA, "storage");
    else if(shop.isSellable(Enums::CHICKEN, farmer.id(), chickenCount())!= Enums::OK)
        err = getNotEnoughError(Enums::CHICKEN, " storage");
    else if(shop.isSellable(Enums::COW, farmer.id(), cowcount())!= Enums::OK)
        err = getNotEnoughError(Enums::COW, "storage");
    else if(shop.isSellable(Enums::SHEEP, farmer.id(), sheepCount())!= Enums::OK)
        err = getNotEnoughError(Enums::SHEEP, "storage");
    else if(shop.isSellable(Enums::NAIL, farmer.id(), nailCount())!= Enums::OK)
        err = getNotEnoughError(Enums::NAIL, "storage");
    else if(shop.isSellable(Enums::SHOVEL, farmer.id(), shovelCount())!= Enums::OK)
        err = getNotEnoughError(Enums::SHOVEL, "storage");
    else if(shop.isSellable(Enums::EGG, farmer.id(), eggCount())!= Enums::OK)
        err = getNotEnoughError(Enums::EGG , "storage");
    else if(shop.isSellable(Enums::MILK, farmer.id(), milkCount())!= Enums::OK)
        err = getNotEnoughError(Enums::MILK , "storage");
    else if(shop.isSellable(Enums::WOOL, farmer.id(), woolCount())!= Enums::OK)
        err = getNotEnoughError(Enums::WOOL, "storage");
    else
    {
        int xp_to_add = 0;

        if(wheatCount() != 0)
            xp_to_add += Shop::sell_xp;
        if(alfalfaCount() != 0)
            xp_to_add += Shop::sell_xp;
        if(chickenCount() != 0)
            xp_to_add += Shop::sell_xp;
        if(eggCount() != 0)
            xp_to_add += Shop::sell_xp;
        if(cowcount() != 0)
            xp_to_add += Shop::sell_xp;
        if(milkCount() != 0)
            xp_to_add += Shop::sell_xp;
        if(sheepCount() != 0)
            xp_to_add += Shop::sell_xp;
        if(woolCount() != 0)
            xp_to_add += Shop::sell_xp;
        if(nailCount() != 0)
            xp_to_add += Shop::sell_xp;
        if(shovelCount() != 0)
            xp_to_add += Shop::sell_xp;

        shop.sell(Enums::WHEAT, farmer.id(), wheatCount());
        shop.sell(Enums::ALFALFA, farmer.id(), alfalfaCount());
        shop.sell(Enums::CHICKEN, farmer.id(), chickenCount());
        shop.sell(Enums::COW, farmer.id(), cowcount());
        shop.sell(Enums::SHEEP, farmer.id(), sheepCount());
        shop.sell(Enums::NAIL, farmer.id(), nailCount());
        shop.sell(Enums::SHOVEL, farmer.id(), shovelCount());
        shop.sell(Enums::EGG, farmer.id(), eggCount());
        shop.sell(Enums::MILK, farmer.id(), milkCount());
        shop.sell(Enums::WOOL, farmer.id(), woolCount());

        emit ShowCoin();
        MessageDialog w("The sale operation was successful!", "Info", this);
        w.exec();

        emit AddXP(xp_to_add);
        show_error = false;
    }

    if(show_error)
    {
        MessageDialog dialog(err, "Error", this);
        dialog.exec();
    }
}

int ShopDialog::wheatCount()
{
    return ui->lblWheat->text().toInt();
}

int ShopDialog::cowcount()
{
    return ui->lblCow->text().toInt();
}

int ShopDialog::alfalfaCount()
{
    return ui->lblAlfalfa->text().toInt();
}

int ShopDialog::milkCount()
{
    return ui->lblMilk->text().toInt();
}

int ShopDialog::chickenCount()
{
    return ui->lblChicken->text().toInt();
}

int ShopDialog::eggCount()
{
    return ui->lblEgg->text().toInt();
}

int ShopDialog::sheepCount()
{
    return ui->lblSheep->text().toInt();
}

int ShopDialog::woolCount()
{
    return ui->lblWool->text().toInt();
}

int ShopDialog::nailCount()
{
    return ui->lblNail->text().toInt();
}

int ShopDialog::shovelCount()
{
    return ui->lblShovel->text().toInt();
}

QString ShopDialog::getNotEnoughError(int type, QString err_name)
{
    QString place = "";
    switch (type)
    {
    case Enums::WHEAT:
        place = "Silo";
        break;
    case Enums::CHICKEN:
        place = "Chicken coop";
        break;
    case Enums::COW:
        place = "Cow pasture";
        break;
    case Enums::SHEEP:
        place = "Sheep pasture";
        break;
    case Enums::ALFALFA:
    case Enums::EGG:
    case Enums::MILK:
    case Enums::WOOL:
    case Enums::NAIL:
    case Enums::SHOVEL:
        place = "Barn";
        break;
    default:
        break;
    }
    return "You don't have enough " + err_name + " in " + place + "!";
}

void ShopDialog::openLockCowMilk()
{
    delete ui->cowLock;
    delete ui->milkLock;

    ui->btnCowPlus->setEnabled(true);
    ui->btnCowMinus->setEnabled(true);

    ui->btnMilkPlus->setEnabled(true);
    ui->btnMilkMinus->setEnabled(true);
}

void ShopDialog::openLockSheepWool()
{
    delete ui->sheepLock;
    delete ui->woolLock;

    ui->btnSheepPlus->setEnabled(true);
    ui->btnSheepMinus->setEnabled(true);

    ui->btnWoolPlus->setEnabled(true);
    ui->btnWoolMinus->setEnabled(true);
}

void ShopDialog::checkLock()
{
    if(farmer.level() >= 3)
        openLockAlfalfa();
    else
        lockAlfalfa();

    if(farmer.level() >= 4)
        openLockCowMilk();
    else
        lockCowMilk();

    if(farmer.level() >= 6)
        openLockSheepWool();
    else
        lockSheepWool();
}

void ShopDialog::lockSheepWool()
{
    ui->btnSheepPlus->setEnabled(false);
    ui->btnSheepMinus->setEnabled(false);

    ui->btnWoolPlus->setEnabled(false);
    ui->btnWoolMinus->setEnabled(false);
}

void ShopDialog::lockCowMilk()
{
    ui->btnCowPlus->setEnabled(false);
    ui->btnCowMinus->setEnabled(false);

    ui->btnMilkPlus->setEnabled(false);
    ui->btnMilkMinus->setEnabled(false);
}

void ShopDialog::lockAlfalfa()
{
    ui->btnAlfalfaPlus->setEnabled(false);
    ui->btnAlfalfaMinus->setEnabled(false);
}

void ShopDialog::on_btnWheatPlus_clicked()
{
    int count = ui->lblWheat->text().toInt();
    if(count < 100)
    {
        ui->lblWheat->setNum(count + 1);
        buyAmount += Shop::wheat_buy_coins;
        sellAmount += Shop::wheat_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnWheatMinus_clicked()
{
    int count = ui->lblWheat->text().toInt();
    if(count > 0)
    {
        ui->lblWheat->setNum(count - 1);
        buyAmount -= Shop::wheat_buy_coins;
        sellAmount -= Shop::wheat_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnShovelPlus_clicked()
{
    int count = ui->lblShovel->text().toInt();
    if(count < 100)
    {
        ui->lblShovel->setNum(count + 1);
        buyAmount += Shop::shovel_buy_coins;
        sellAmount += Shop::shovel_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnShovelMinus_clicked()
{
    int count = ui->lblShovel->text().toInt();
    if(count > 0)
    {
        ui->lblShovel->setNum(count - 1);
        buyAmount -= Shop::shovel_buy_coins;
        sellAmount -= Shop::shovel_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnNailPlus_clicked()
{
    int count = ui->lblNail->text().toInt();
    if(count < 100)
    {
        ui->lblNail->setNum(count + 1);
        buyAmount += Shop::nail_buy_coins;
        sellAmount += Shop::nail_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnNailMinus_clicked()
{
    int count = ui->lblNail->text().toInt();
    if(count > 0)
    {
        ui->lblNail->setNum(count - 1);
        buyAmount -= Shop::nail_buy_coins;
        sellAmount -= Shop::nail_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnChickenPlus_clicked()
{
    int count = ui->lblChicken->text().toInt();
    if(count < 100)
    {
        ui->lblChicken->setNum(count + 1);
        buyAmount += Shop::chicken_buy_coins;
        sellAmount += Shop::chicken_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnChickenMinus_clicked()
{
    int count = ui->lblChicken->text().toInt();
    if(count > 0)
    {
        ui->lblChicken->setNum(count - 1);
        buyAmount -= Shop::chicken_buy_coins;
        sellAmount -= Shop::chicken_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnEggPlus_clicked()
{
    int count = ui->lblEgg->text().toInt();
    if(count < 100)
    {
        ui->lblEgg->setNum(count + 1);
        sellAmount += Shop::egg_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnEggMinus_clicked()
{
    int count = ui->lblEgg->text().toInt();
    if(count > 0)
    {
        ui->lblEgg->setNum(count - 1);
        sellAmount -= Shop::egg_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnAlfalfaPlus_clicked()
{
    int count = ui->lblAlfalfa->text().toInt();
    if(count < 100)
    {
        ui->lblAlfalfa->setNum(count + 1);
        buyAmount += Shop::alfalfa_buy_coins;
        sellAmount += Shop::alfalfa_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnAlfalfaMinus_clicked()
{
    int count = ui->lblAlfalfa->text().toInt();
    if(count > 0)
    {
        ui->lblAlfalfa->setNum(count - 1);
        buyAmount -= Shop::alfalfa_buy_coins;
        sellAmount -= Shop::alfalfa_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnCowPlus_clicked()
{
    int count = ui->lblCow->text().toInt();
    if(count < 100)
    {
        ui->lblCow->setNum(count + 1);
        buyAmount += Shop::cow_buy_coins;
        sellAmount += Shop::cow_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnCowMinus_clicked()
{
    int count = ui->lblCow->text().toInt();
    if(count > 0)
    {
        ui->lblCow->setNum(count - 1);
        buyAmount -= Shop::cow_buy_coins;
        sellAmount -= Shop::cow_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnMilkPlus_clicked()
{
    int count = ui->lblMilk->text().toInt();
    if(count < 100)
    {
        ui->lblMilk->setNum(count + 1);
        sellAmount += Shop::milk_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnMilkMinus_clicked()
{
    int count = ui->lblMilk->text().toInt();
    if(count > 0)
    {
        ui->lblMilk->setNum(count - 1);
        sellAmount -= Shop::milk_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnSheepPlus_clicked()
{
    int count = ui->lblSheep->text().toInt();
    if(count < 100)
    {
        ui->lblSheep->setNum(count + 1);
        buyAmount += Shop::sheep_buy_coins;
        sellAmount += Shop::sheep_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnSheepMinus_clicked()
{
    int count = ui->lblSheep->text().toInt();
    if(count > 0)
    {
        ui->lblSheep->setNum(count - 1);
        buyAmount -= Shop::sheep_buy_coins;
        sellAmount -= Shop::sheep_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnWoolPlus_clicked()
{
    int count = ui->lblWool->text().toInt();
    if(count < 100)
    {
        ui->lblWool->setNum(count + 1);
        sellAmount += Shop::wool_sell_coins;

        showAmount();
    }
}

void ShopDialog::on_btnWoolMinus_clicked()
{
    int count = ui->lblWool->text().toInt();
    if(count > 0)
    {
        ui->lblWool->setNum(count - 1);
        sellAmount -= Shop::wool_sell_coins;

        showAmount();
    }
}


void ShopDialog::on_btnBuy_clicked()
{
    if(buyAmount != 0)
    {
        if(farmer.coins() > buyAmount)
            buy();
        else
        {
            MessageDialog w("You don't have enough coins!", "Error", this);
            w.exec();
        }
    }
    else
    {
        MessageDialog w("Please pick an item!", "Error", this);
        w.exec();
    }
}

void ShopDialog::on_btnSell_clicked()
{
    if(sellAmount != 0)
    {
        sell();
    }
    else
    {
        MessageDialog w("Please pick an item!", "Error", this);
        w.exec();
    }
}
