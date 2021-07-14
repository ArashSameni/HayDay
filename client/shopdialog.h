#ifndef SHOPDIALOG_H
#define SHOPDIALOG_H

#include <QDialog>
#include "shop.h"

namespace Ui {
class ShopDialog;
}

class ShopDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShopDialog(QWidget *parent = nullptr);
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

private:
    Ui::ShopDialog *ui;
    int buyAmount = 0;
    int sellAmount = 0;

    void showAmount();
    void showBuyButton();
    void showSellButton();
};

#endif // SHOPDIALOG_H
