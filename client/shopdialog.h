#ifndef SHOPDIALOG_H
#define SHOPDIALOG_H

#include <QDialog>
#include "shop.h"
#include "farmer.h"

namespace Ui {
class ShopDialog;
}

class ShopDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShopDialog(Farmer& farmer,QWidget *parent = nullptr);
    ~ShopDialog();

private slots:
    void on_btnWheatPlus_clicked();

    void on_btnWheatMinus_clicked();

    void on_btnShovelPlus_clicked();

    void on_btnShovelMinus_clicked();

    void on_btnNailPlus_clicked();

    void on_btnNailMinus_clicked();

    void on_btnChickenPlus_clicked();

    void on_btnChickenMinus_clicked();

    void on_btnEggPlus_clicked();

    void on_btnEggMinus_clicked();

    void on_btnAlfalfaPlus_clicked();

    void on_btnAlfalfaMinus_clicked();

    void on_btnCowPlus_clicked();

    void on_btnCowMinus_clicked();

    void on_btnMilkPlus_clicked();

    void on_btnMilkMinus_clicked();

    void on_btnSheepPlus_clicked();

    void on_btnSheepMinus_clicked();

    void on_btnWoolPlus_clicked();

    void on_btnWoolMinus_clicked();

    void on_btnBuy_clicked();

    void on_btnSell_clicked();

signals:
    void AddXP(int);
    void ShowCoin();
    void ShowChickens();
    void ShowCows();
    void ShowSheeps();

private:
    Ui::ShopDialog *ui;
    int buyAmount = 0;
    int sellAmount = 0;
    Farmer& farmer;
    Shop shop;

    void showAmount();
    void showBuyButton();
    void showSellButton();

    void checkLock();
    void lockSheepWool();
    void lockCowMilk();
    void lockAlfalfa();
    void openLockSheepWool();
    void openLockCowMilk();
    void openLockAlfalfa();
    void buy();
    void sell();
    void resetAmounts();

    int wheatCount();
    int cowCount();
    int milkCount();
    int sheepCount();
    int woolCount();
    int alfalfaCount();
    int chickenCount();
    int eggCount();
    int nailCount();
    int shovelCount();

    QString getNotEnoughError(int type, QString err_name);
};

#endif // SHOPDIALOG_H
