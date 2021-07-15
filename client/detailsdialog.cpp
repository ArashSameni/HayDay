#include "detailsdialog.h"
#include "ui_detailsdialog.h"
#include "globals.h"
#include <QMessageBox>

DetailsDialog::DetailsDialog(QString title, Farmer& farmer, Farm& farm, QWidget *parent) :
    QDialog(parent), ui(new Ui::DetailsDialog),
    farmer(farmer), farm(farm)
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    if(title == "Silo")
    {
        current_place = SILO;
        initialSilo();
    }
}

DetailsDialog::~DetailsDialog()
{
    delete ui;
}

void DetailsDialog::initialByPlace(const Place &place)
{
    ui->lblLevel->setText("Level: " + QString::number(farmer.level()));

    ui->lblUpgradeShovel->setText(QString::number(farm.barn().shovels()) + "/" +
                                  QString::number(place.neededShovelsToUpgrade()));

    ui->lblUpgradeNail->setText(QString::number(farm.barn().nails()) + "/" +
                                  QString::number(place.neededNailsToUpgrade()));

    ui->lblUpgradeTime->setText(QString::number(place.upgrade_time) + " Days");

    ui->btnUpgrade->setText(QString::number(place.neededCoinsToUpgrade()));

    if(place.is_upgrading())
    {
        //Disable upgrade button
        ui->btnUpgrade->setCursor(Qt::ArrowCursor);
        ui->btnUpgrade->setStyleSheet("QPushButton{\n	border: none;\n	color: #fff;\n	background-image: url(:/img/upgrade-btn-disabled.png);\n}");
        ui->btnUpgrade->setEnabled(false);

        //Show Remaining Days of upgrade
        int remaining_days = place.upgrade_time + place.upgrade_day() - CURRENT_DAY;
        ui->lblDaysLeft->setText(QString::number(remaining_days) + " Days Left");
        ui->lblDaysLeft->show();
    }
    else
        ui->lblDaysLeft->hide();
}

void DetailsDialog::initialSilo()
{
    Silo& silo = farm.silo();
    initialByPlace(silo);

    ui->lblStorage->setText("Storage: " + QString::number(silo.storage()) + "/" + QString::number(silo.max_storage()));
    int new_storage = 2 * silo.max_storage();
    ui->lblUpgradeInfo->setText("Max-storage will be " + QString::number(new_storage));
}

void DetailsDialog::upgradeSilo()
{
    Silo& silo = farm.silo();
    int res = silo.isUpgradable(farmer.id());
    if(res == Enums::OK)
    {
        silo.upgrade();
        QMessageBox::information(this, "Info", "Silo is now upgrading");
        initialSilo();
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
            err = "you have not reached required level to upgrade";

        QMessageBox::warning(this, "Error", err);
    }

}

void DetailsDialog::on_btnUpgrade_clicked()
{
    switch (current_place)
    {
    case SILO:
        upgradeSilo();
        break;
    default:
        break;
    }
}
