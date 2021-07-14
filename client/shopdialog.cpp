#include "shopdialog.h"
#include "ui_shopdialog.h"

ShopDialog::ShopDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShopDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
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
