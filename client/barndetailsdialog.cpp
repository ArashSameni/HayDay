#include "barndetailsdialog.h"
#include "ui_barndetailsdialog.h"
#include "globals.h"
#include <QMessageBox>
#include <QtMath>

BarnDetailsDialog::BarnDetailsDialog(Farmer& farmer, Farm& farm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BarnDetailsDialog),
    farmer(farmer), farm(farm)
{
    ui->setupUi(this);
    this->setWindowTitle("Barn");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    initUI();
    showBarn();
}

BarnDetailsDialog::~BarnDetailsDialog()
{
    delete ui;
}

void BarnDetailsDialog::on_lblUpgrade_clicked()
{
    if(isBarnShown)
        showUpgrade();
    else
        showBarn();

    isBarnShown = !isBarnShown;
}

void BarnDetailsDialog::initUI()
{
    initBarn();
    initUpgrade();
}

void BarnDetailsDialog::initUpgrade()
{
    Barn& barn = farm.barn();

    ui->lblLevel->setText("Level: " + QString::number(barn.level()));

    ui->lblStorage->setText("Storage: " + QString::number(barn.storage()) + "/" + QString::number(barn.max_storage()));

    ui->lblUpgradeShovel->setText(QString::number(barn.shovels()) + "/" +
                                  QString::number(barn.neededShovelsToUpgrade()));

    ui->lblUpgradeNail->setText(QString::number(barn.nails()) + "/" +
                                QString::number(barn.neededNailsToUpgrade()));

    ui->lblUpgradeTime->setText(QString::number(barn.upgrade_time) + " Days");

    ui->btnUpgrade->setText(QString::number(barn.neededCoinsToUpgrade()));

    int new_storage = qCeil(1.5 * barn.max_storage());
    ui->lblUpgradeInfo->setText("Max-storage will be " + QString::number(new_storage));

    if(barn.is_upgrading())
    {
        //Disable upgrade button
        ui->btnUpgrade->setCursor(Qt::ArrowCursor);
        ui->btnUpgrade->setStyleSheet("QPushButton{\n	border: none;\n	color: #fff;\n	background-image: url(:/img/upgrade-btn-disabled.png);\n}");
        ui->btnUpgrade->setEnabled(false);

        //Show Remaining Days of upgrade
        int remaining_days = barn.upgrade_time + barn.upgrade_day() - CURRENT_DAY;
        ui->lblDaysLeft->setText(QString::number(remaining_days) + " Days Left");
        ui->lblDaysLeft->show();
    }
    else
        ui->lblDaysLeft->hide();
}

void BarnDetailsDialog::initBarn()
{
    Barn& barn = farm.barn();

    ui->lblEgg->setText(QString::number(barn.eggs()));
    ui->lblMilk->setText(QString::number(barn.milks()));
    ui->lblNail->setText(QString::number(barn.nails()));
    ui->lblWool->setText(QString::number(barn.wools()));
    ui->lblShovel->setText(QString::number(barn.shovels()));
    ui->lblAlfalfa->setText(QString::number(barn.alfalfas()));
}

void BarnDetailsDialog::showUpgrade()
{
    this->setStyleSheet("*{\n	font: 24px \"IRANSans Light\";\n	color: #494949;\n}\n\n#BarnDetailsDialog { background-image: url(:/img/details-bg.png) }");

    ui->lblEgg->hide();
    ui->lblMilk->hide();
    ui->lblNail->hide();
    ui->lblWool->hide();
    ui->lblShovel->hide();
    ui->lblAlfalfa->hide();

    ui->lblUpgrade->setText("> Details");

    ui->lblUpgradeShovel->show();
    ui->lblUpgradeNail->show();
    ui->lblUpgradeTime->show();
    ui->btnUpgrade->show();
    ui->lblUpgradeInfo->show();
    if(farm.barn().is_upgrading())
        ui->lblDaysLeft->show();
}

void BarnDetailsDialog::showBarn()
{
    this->setStyleSheet("*{\n	font: 24px \"IRANSans Light\";\n	color: #494949;\n}\n\n#BarnDetailsDialog { background-image: url(:/img/barn-bg.png) }");

    ui->lblEgg->show();
    ui->lblMilk->show();
    ui->lblNail->show();
    ui->lblWool->show();
    ui->lblShovel->show();
    ui->lblAlfalfa->show();

    ui->lblUpgrade->setText("> Upgrade");

    ui->lblUpgradeShovel->hide();
    ui->lblUpgradeNail->hide();
    ui->lblUpgradeTime->hide();
    ui->btnUpgrade->hide();
    ui->lblUpgradeInfo->hide();
    ui->lblDaysLeft->hide();
}

void BarnDetailsDialog::upgradeBarn()
{
    Barn& barn = farm.barn();
    int res = barn.isUpgradable(farmer.id());
    if(res == Enums::OK)
    {
        barn.upgrade(farmer, barn.id());
        QMessageBox::information(this, "Info", "Barn is now upgrading");
        initUpgrade();
    }
    else
    {
        QString err;
        if(res == Enums::LACK_OF_COINS)
            err = "You don't have enough coins!";
        else if(res == Enums::LACK_OF_NAILS)
            err = "You don't have enough nails!";
        else if(res == Enums::LACK_OF_SHOVELS)
            err = "You don't have enough shovels!";
        else if(res == Enums::LACK_OF_LEVEL)
            err = "You have not reached required level to upgrade";

        QMessageBox::warning(this, "Error", err);
    }
}

void BarnDetailsDialog::on_btnUpgrade_clicked()
{
    upgradeBarn();
}
