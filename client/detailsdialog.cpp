#include "detailsdialog.h"
#include "ui_detailsdialog.h"
#include "globals.h"
#include <QMessageBox>

DetailsDialog::DetailsDialog(QString title, Farmer &farmer, Farm &farm, QWidget *parent) : QDialog(parent), ui(new Ui::DetailsDialog),
                                                                                           farmer(farmer), farm(farm)
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    if (title == "Silo")
    {
        current_place = SILO;
        initialSilo();
    }
    else if (title == "Chicken Coop")
    {
        current_place = CHICKEN_COOP;
        initialLivingPlace(farm.chicken_coop());
    }
    else if (title == "Cow Pasture")
    {
        current_place = COW_PASTURE;
        initialLivingPlace(farm.cow_pasture());
    }
    else if (title == "Sheep Pasture")
    {
        current_place = SHEEP_PASTURE;
        initialLivingPlace(farm.sheep_pasture());
    }
    else if (title == "Wheat Field")
    {
        current_place = WHEAT_FIELD;
        initialField(farm.wheat_field());
    }
    else if (title == "Alfalfa Field")
    {
        current_place = ALFALFA_FIELD;
        initialField(farm.alfalfa_field());
    }
}

DetailsDialog::~DetailsDialog()
{
    delete ui;
}

void DetailsDialog::initialByPlace(const Place &place)
{
    ui->lblLevel->setText("Level: " + QString::number(place.level()));

    ui->lblUpgradeShovel->setText(QString::number(farm.barn().shovels()) + "/" +
                                  QString::number(place.neededShovelsToUpgrade()));

    ui->lblUpgradeNail->setText(QString::number(farm.barn().nails()) + "/" +
                                QString::number(place.neededNailsToUpgrade()));

    ui->lblUpgradeTime->setText(QString::number(place.upgrade_time) + " Days");

    ui->btnUpgrade->setText(QString::number(place.neededCoinsToUpgrade()));

    if (place.is_upgrading())
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
    Silo &silo = farm.silo();
    initialByPlace(silo);

    ui->lblStorage->setText("Storage: " + QString::number(silo.storage()) + "/" + QString::number(silo.max_storage()));
    int new_storage = 2 * silo.max_storage();
    ui->lblUpgradeInfo->setText("Max-storage will be " + QString::number(new_storage));
}

void DetailsDialog::upgradeSilo()
{
    Silo &silo = farm.silo();
    int res = silo.isUpgradable(farmer.id());
    if (res == Enums::OK)
    {
        silo.upgrade(farmer, farm.barn().id());
        QMessageBox::information(this, "Info", "Silo is now upgrading");
        initialSilo();
    }
    else
    {
        QString err;
        if (res == Enums::LACK_OF_COINS)
            err = "You don't have enough coins!";
        else if (res == Enums::LACK_OF_NAILS)
            err = "You don't have enough nails!";
        else if (res == Enums::LACK_OF_SHOVELS)
            err = "You don't have enough shovels!";
        else if (res == Enums::LACK_OF_LEVEL)
            err = "You have not reached required level to upgrade";

        QMessageBox::warning(this, "Error", err);
    }
}

void DetailsDialog::initialLivingPlace(const LivingPlace &place)
{
    initialByPlace(place);

    ui->lblStorage->setText("Storage: " + QString::number(place.storage()) + "/" + QString::number(place.max_storage()));
    int new_storage = 2 * place.max_storage();
    if (new_storage == 0)
        new_storage = 2;
    ui->lblUpgradeInfo->setText("Max-storage will be " + QString::number(new_storage));

    //Show Feed/Collect Button
    ui->btnUpgrade->move(46, 313);
    btnFeedCollect = new QPushButton(this);
    btnFeedCollect->setStyleSheet("QPushButton{\n	border: none;\n	border-radius: 10px;\n	background-color: #e0b943;\n	color: #fff;\n}\n\nQPushButton:hover{\n	background-color: #c9a63c;\n}");
    btnFeedCollect->setCursor(Qt::PointingHandCursor);
    if (place.animals_condition() == Enums::HUNGRY)
        btnFeedCollect->setText("Feed");
    else
        btnFeedCollect->setText("Collect");
    btnFeedCollect->setGeometry(241, 313, 162, 49);
}

void DetailsDialog::upgradeLivingPlace(LivingPlace &place)
{
    int res = place.isUpgradable(farmer.id());
    if (res == Enums::OK)
    {
        place.upgrade(farmer, farm.barn().id());
        QMessageBox::information(this, "Info", "Place is now upgrading");
        initialLivingPlace(place);
    }
    else
    {
        QString err;
        if (res == Enums::LACK_OF_COINS)
            err = "You don't have enough coins!";
        else if (res == Enums::LACK_OF_NAILS)
            err = "You don't have enough nails!";
        else if (res == Enums::LACK_OF_SHOVELS)
            err = "You don't have enough shovels!";
        else if (res == Enums::LACK_OF_LEVEL)
            err = "You have not reached required level to upgrade";

        QMessageBox::warning(this, "Error", err);
    }
}

void DetailsDialog::initialField(const Field &field)
{
    initialByPlace(field);

    ui->lblStorage->setText("Planted area: " + QString::number(field.planted_area()) + "/" + QString::number(field.area()));
    int new_area = 2 * field.area();
    if (new_area == 0)
        new_area = 4;
    ui->lblUpgradeInfo->setText("New area will be " + QString::number(new_area));

    //Show Plant/Reap Button
    ui->btnUpgrade->move(46, 313);
    if(btnFeedCollect == nullptr)
    {
        btnFeedCollect = new QPushButton(this);
        btnFeedCollect->setStyleSheet("QPushButton{\n	border: none;\n	border-radius: 10px;\n	background-color: #e0b943;\n	color: #fff;\n}\n\nQPushButton:hover{\n	background-color: #c9a63c;\n}");
        btnFeedCollect->setCursor(Qt::PointingHandCursor);
        btnFeedCollect->setGeometry(241, 313, 162, 49);
    }

    if (current_place == WHEAT_FIELD && field.plants_condition() == Enums::NOT_PLANTED)
        btnFeedCollect->setText("Plant");
    else if (current_place == ALFALFA_FIELD)
    {
        const AlfalfaField &alfalfa_field = *dynamic_cast<const AlfalfaField *>(&field);
        if (alfalfa_field.plants_condition() == Enums::NOT_PLOWED)
            btnFeedCollect->setText("Plow");
        else if (field.plants_condition() == Enums::NOT_PLANTED)
            btnFeedCollect->setText("Plant");
        else
            btnFeedCollect->setText("Reap");
    }
    else
        btnFeedCollect->setText("Reap");

    connect(btnFeedCollect, &QPushButton::clicked, this, &DetailsDialog::on_btnFeed_clicked);
}

void DetailsDialog::upgradeField(Field &field)
{
    int res = field.isUpgradable(farmer.id());
    if (res == Enums::OK)
    {
        field.upgrade(farmer, farm.barn().id());
        QMessageBox::information(this, "Info", "Field is now upgrading");
        initialField(field);
    }
    else
    {
        QString err;
        if (res == Enums::LACK_OF_COINS)
            err = "You don't have enough coins!";
        else if (res == Enums::LACK_OF_NAILS)
            err = "You don't have enough nails!";
        else if (res == Enums::LACK_OF_SHOVELS)
            err = "You don't have enough shovels!";
        else if (res == Enums::LACK_OF_LEVEL)
            err = "You have not reached required level to upgrade";

        QMessageBox::warning(this, "Error", err);
    }
}

void DetailsDialog::plowField(AlfalfaField &field)
{
    int res = field.isPlowable(farmer.id());
    if (res == Enums::OK)
    {
        field.plow();
        QMessageBox::information(this, "Info", "field is now plowing");
        initialField(field);
    }
    else
    {
        QString err;
        if (res == Enums::LACK_OF_COINS)
            err = "You don't have enough coins!";
        else if (err == Enums::PLOWING || err == Enums::PLOWED)
            err = "You have already plowed this filed!";
        else if (err == Enums::PLANTED)
            err = "You have planted alfalfa in this field!";

        QMessageBox::warning(this, "Error", err);
    }
}

void DetailsDialog::plantField(int amount, Field &field)
{
    //    if(current_place==ALFALFA_FIELD && !farm.alfalfa_field().isPlowingFinished())
    //        err="Plowing is not finished yet!";
    //xpxpxpxpxpx

    int res = 0, storage_place_id = 0;
    QString err;
    if (current_place == WHEAT_FIELD)
        storage_place_id = farm.silo().id();
    else if (current_place == ALFALFA_FIELD)
        storage_place_id = farm.barn().id();

    res = field.isPlantable(storage_place_id, amount);

    if (res == Enums::OK)
    {
        field.plant(storage_place_id, amount);
        QMessageBox::information(this, "Info", "Field is now planted");
        initialField(field);
    }
    else
    {
        if (err == Enums::AREA_ERROR)
            err = "You don't have enough space for planting!";
        else if (err == Enums::LACK_OF_SEED)
            err = "You don't have enough seed for planting!";
        else if (err == Enums::NOT_PLOWED)
            err = "This field should be plowed first!";
        else if (err == Enums::PLOWING)
            err = "Plowing is not finished!";
        else if (err == Enums::PLANTED)
            err = "Field is already planted!";

        QMessageBox::warning(this, "Error", err);
    }
}

void DetailsDialog::reapField(Field &field)
{
    int storage_place_id = 0;
    int res;
    if (field.isReapTime())
    {
        if (current_place == WHEAT_FIELD)
            storage_place_id = farm.silo().id();
        else if (current_place == ALFALFA_FIELD)
            storage_place_id = farm.barn().id();
        res = field.isReapable(storage_place_id);
        if (res == Enums::OK)
        {
            field.reap(storage_place_id);
            QMessageBox::information(this, "Info", "Field is reaped");
            initialField(field);
        }
        else
        {
            QString err;
            if (current_place == WHEAT_FIELD )
                err = "You don't have enough space in your silo!";

            else if (current_place == ALFALFA_FIELD)
                err = "You don't have enough space in barn!";


            QMessageBox::warning(this, "Error", err);
        }
    }
    else
        QMessageBox::warning(this, "Error", "Plants' growing is not finished yet!");
}

void DetailsDialog::on_btnUpgrade_clicked()
{
    switch (current_place)
    {
    case SILO:
        upgradeSilo();
        break;
    case CHICKEN_COOP:
    case COW_PASTURE:
    case SHEEP_PASTURE:
        if (current_place == CHICKEN_COOP)
            upgradeLivingPlace(farm.chicken_coop());
        else if (current_place == COW_PASTURE)
            upgradeLivingPlace(farm.cow_pasture());
        else if (current_place == SHEEP_PASTURE)
            upgradeLivingPlace(farm.sheep_pasture());
        break;
    case WHEAT_FIELD:
    case ALFALFA_FIELD:
        if (current_place == WHEAT_FIELD)
            upgradeField(farm.wheat_field());
        else if (current_place == ALFALFA_FIELD)
            upgradeField(farm.alfalfa_field());
        break;
    default:
        break;
    }
}

void DetailsDialog::on_btnFeed_clicked()
{
    int amount = 0; //get from user,it should be less than max area
    switch (current_place)
    {
    case WHEAT_FIELD:
        if (farm.wheat_field().plants_condition() == Enums::NOT_PLANTED)
            plantField(amount, farm.wheat_field());
        else if (farm.wheat_field().plants_condition() == Enums::PLANTED)
            reapField(farm.wheat_field());
        break;

    case ALFALFA_FIELD:
        if (farm.alfalfa_field().plants_condition() == Enums::NOT_PLANTED)
            plowField(farm.alfalfa_field());
        else if (farm.alfalfa_field().plants_condition() == Enums::PLOWED)
            plantField(amount, farm.alfalfa_field());
        else if (farm.alfalfa_field().plants_condition() == Enums::PLANTED)
            reapField(farm.alfalfa_field());
        break;
    }
}
