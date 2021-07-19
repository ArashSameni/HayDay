#include "detailsdialog.h"
#include "ui_detailsdialog.h"
#include "globals.h"
#include "messagedialog.h"
#include "levelupdialog.h"

DetailsDialog::DetailsDialog(QString title, Farmer &farmer, Farm &farm, QWidget *parent) : QDialog(parent), ui(new Ui::DetailsDialog),
    farmer(farmer), farm(farm)
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->lblWheatIcon->hide();
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
    initSounds();
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
        disableUpgradeButton();

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
    ui->lblWheatIcon->show();
    Silo &silo = farm.silo();
    initialByPlace(silo);

    ui->lblStorage->setText("Storage: " + QString::number(silo.storage()) + "/" + QString::number(silo.max_storage()));
    int new_storage = 2 * silo.max_storage();
    ui->lblInfo->setText("Max-storage will be " + QString::number(new_storage));
}

void DetailsDialog::upgradeSilo()
{
    Silo &silo = farm.silo();
    int res = silo.isUpgradable(farmer.id());
    if (res == Enums::OK)
    {
        silo.upgrade(farmer, farm.barn().id());
        emit ShowCoin();
        MessageDialog w("Silo is now upgrading", "Info", this);
        w.exec();
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

        MessageDialog w(err, "Error", this);
        w.exec();
    }
}

void DetailsDialog::initialLivingPlace(const LivingPlace &place)
{
    initialByPlace(place);

    ui->lblStorage->setText("Storage: " + QString::number(place.storage()) + "/" + QString::number(place.max_storage()));
    int new_storage = 2 * place.max_storage();
    if (new_storage == 0)
        new_storage = 2;
    ui->lblInfo->setText("Max-storage will be " + QString::number(new_storage));

    //Show Feed/Collect Button
    if (btnFeedCollect == nullptr)
    {
        ui->btnUpgrade->move(46, 313);
        btnFeedCollect = new QPushButton(this);
        btnFeedCollect->setStyleSheet("QPushButton{\n	border: none;\n	border-radius: 10px;\n	background-color: #e0b943;\n	color: #fff;\n}\n\nQPushButton:hover{\n	background-color: #c9a63c;\n}");
        btnFeedCollect->setCursor(Qt::PointingHandCursor);
        btnFeedCollect->setGeometry(241, 313, 162, 49);
        connect(btnFeedCollect, &QPushButton::clicked, this, &DetailsDialog::on_btnFeed_clicked);
    }

    if(place.level() == 0 || place.storage() == 0)
        disableFeedCollectButton();
    else if (place.animals_condition() == Enums::HUNGRY)
        btnFeedCollect->setText("Feed");
    else
    {
        if(current_place == SHEEP_PASTURE)
        {
            int needed_coins_to_breed = place.storage();
            btnFeedCollect->setText("Collect - " + QString::number(needed_coins_to_breed));
        }
        else
            btnFeedCollect->setText("Collect");

        if(!place.isCollectTime())
        {
            disableFeedCollectButton();
            int collecting_time = 0;
            if(current_place == CHICKEN_COOP)
                collecting_time = dynamic_cast<const ChickenCoop*>(&place)->collecting_time;
            else if(current_place == COW_PASTURE)
                collecting_time = dynamic_cast<const CowPasture*>(&place)->collecting_time;
            else
                collecting_time = dynamic_cast<const SheepPasture*>(&place)->collecting_time;

            int remained_days = collecting_time + place.feeding_day() - CURRENT_DAY;
            ui->lblInfo->setText(QString::number(remained_days) + " Days left to collect products");
        }
    }
}

void DetailsDialog::upgradeLivingPlace(LivingPlace &place)
{
    int res = place.isUpgradable(farmer.id());
    if (res == Enums::OK)
    {
        place.upgrade(farmer, farm.barn().id());
        emit ShowCoin();
        MessageDialog w("Place is now upgrading", "Info", this);
        w.exec();
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

        MessageDialog w(err, "Error", this);
        w.exec();
    }
}

void DetailsDialog::feedLivingPlace(LivingPlace &place)
{
    int res = 0, storage_place_id = 0;
    if (current_place == CHICKEN_COOP)
        storage_place_id = farm.silo().id();
    else
        storage_place_id = farm.barn().id();

    res = place.isFeedable(storage_place_id);
    if (res == Enums::OK)
    {
        place.feed(storage_place_id);
        MessageDialog w("Animals are now fed.", "Info", this);
        w.exec();

        emit AddXP(place.feedXp());

        initialLivingPlace(place);
    }
    else
    {
        QString err;
        if(res == Enums::NO_ANIMALS)
            err = "You don't have any animals!";
        else if (res == Enums::ALREADY_FED)
            err = "Animals are already fed!";
        else
            err = "You don't have enough storage to feed animals!";

        MessageDialog w(err, "Error", this);
        w.exec();
    }
}

void DetailsDialog::collectLivingPlace(LivingPlace &place)
{
    int res, storage_place_id = 0;
    if (place.isCollectTime())
    {
        if (current_place == SHEEP_PASTURE)
            storage_place_id = farmer.id();
        else
            storage_place_id = farm.barn().id();

        res = place.isCollectable(storage_place_id);
        if (res == Enums::OK)
        {
            place.collect(storage_place_id);
            emit ShowCoin();
            MessageDialog w("Products are collected!", "Info", this);
            w.exec();

            emit AddXP(place.collectXp());

            initialLivingPlace(place);
        }
        else
        {
            QString err;
            if (res == Enums::LACK_OF_STORAGE)
                err = "You don't have enough space in barn!";
            else
                err = "You don't have enough money to breed the sheeps!";

            MessageDialog w(err, "Error", this);
            w.exec();
        }
    }
    else
    {
        MessageDialog w("Product is not collectable yet!", "Error", this);
        w.exec();
    }
}

void DetailsDialog::initialField(const Field &field)
{
    initialByPlace(field);

    ui->lblStorage->setText("Planted area: " + QString::number(field.planted_area()) + "/" + QString::number(field.area()));
    int new_area = 2 * field.area();
    if (new_area == 0)
        new_area = 4;
    ui->lblInfo->setText("New area will be " + QString::number(new_area));

    //Show Plant/Reap Button
    if (btnFeedCollect == nullptr)
    {
        ui->btnUpgrade->move(46, 313);
        btnFeedCollect = new QPushButton(this);
        btnFeedCollect->setStyleSheet("QPushButton{\n	border: none;\n	border-radius: 10px;\n	background-color: #e0b943;\n	color: #fff;\n}\n\nQPushButton:hover{\n	background-color: #c9a63c;\n}");
        btnFeedCollect->setCursor(Qt::PointingHandCursor);
        btnFeedCollect->setGeometry(241, 313, 162, 49);
        connect(btnFeedCollect, &QPushButton::clicked, this, &DetailsDialog::on_btnPlant_clicked);
    }

    if(field.level() == 0)
        disableFeedCollectButton();
    else
    {
        if (current_place == WHEAT_FIELD)
        {
            if(field.plants_condition() == Enums::NOT_PLANTED)
                btnFeedCollect->setText("Plant");
            else
            {
                btnFeedCollect->setText("Reap");
                if(field.plants_condition() != Enums::REAPABLE)
                {
                    disableFeedCollectButton();
                    int growing_time = dynamic_cast<const WheatField*>(&field)->growing_time;
                    int remained_days = growing_time + field.planting_day() - CURRENT_DAY;
                    ui->lblInfo->setText(QString::number(remained_days) + " Days left to reap the field");
                }
            }
        }
        else if (current_place == ALFALFA_FIELD)
        {
            const AlfalfaField &alfalfa_field = *dynamic_cast<const AlfalfaField *>(&field);
            if (alfalfa_field.plants_condition() == Enums::NOT_PLOWED)
                btnFeedCollect->setText("Plow - " + QString::number(5 * field.area()));
            else if(field.plants_condition() == Enums::PLOWING)
            {
                btnFeedCollect->setText("Plant");
                disableFeedCollectButton();
            }
            else if (field.plants_condition() == Enums::PLOWED)
                btnFeedCollect->setText("Plant");
            else
            {
                btnFeedCollect->setText("Reap");
                if(field.plants_condition() != Enums::REAPABLE)
                {
                    disableFeedCollectButton();
                    int remained_days = alfalfa_field.growing_time + field.planting_day() - CURRENT_DAY;
                    ui->lblInfo->setText(QString::number(remained_days) + " Days left to reap the field");
                }
            }
        }
    }
}

void DetailsDialog::upgradeField(Field &field)
{
    int res = field.isUpgradable(farmer.id());
    if (res == Enums::OK)
    {
        field.upgrade(farmer, farm.barn().id());
        emit ShowCoin();
        MessageDialog w("Field is now upgrading", "Info", this);
        w.exec();
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


        MessageDialog w(err, "Error", this);
        w.exec();
    }
}

void DetailsDialog::plowField(AlfalfaField &field)
{
    int res = field.isPlowable(farmer.id());
    if (res == Enums::OK)
    {
        field.plow(farmer.id());
        emit ShowCoin();
        MessageDialog w("Field is now plowing", "Info", this);
        w.exec();

        emit AddXP(field.plowXp());

        initialField(field);
    }
    else
    {
        QString err;
        if (res == Enums::LACK_OF_COINS)
            err = "You don't have enough coins!";
        else if (res == Enums::PLOWING || res == Enums::PLOWED)
            err = "You have already plowed this filed!";
        else if (res == Enums::PLANTED)
            err = "You have planted alfalfa in this field!";

        MessageDialog w(err, "Error", this);
        w.exec();
    }
}

void DetailsDialog::plantField(int amount, Field &field)
{
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
        MessageDialog w("Field is now planted", "Info", this);
        w.exec();

        emit AddXP(field.plantXp());

        if(current_place == WHEAT_FIELD)
            emit WheatFieldPlanted();
        else
            emit AlfalfaFieldPlanted();

        initialField(field);
    }
    else
    {
        if (res == Enums::AREA_ERROR)
            err = "You don't have enough space for planting!";
        else if (res == Enums::LACK_OF_SEED)
            err = "You don't have enough seed for planting!";
        else if (res == Enums::NOT_PLOWED)
            err = "This field should be plowed first!";
        else if (res == Enums::PLOWING)
            err = "Plowing is not finished!";
        else if (res == Enums::PLANTED)
            err = "Field is already planted!";


        MessageDialog w(err, "Error", this);
        w.exec();
    }
}

void DetailsDialog::reapField(Field &field)
{
    int storage_place_id = 0;
    if (field.plants_condition() == Enums::REAPABLE)
    {
        if (current_place == WHEAT_FIELD)
            storage_place_id = farm.silo().id();
        else if (current_place == ALFALFA_FIELD)
            storage_place_id = farm.barn().id();

        int count_to_reap = field.reapableCount(storage_place_id);
        if(count_to_reap > field.planted_area())
            count_to_reap = field.planted_area();
        if (count_to_reap)
        {
            if(count_to_reap < field.planted_area())
            {
                MessageDialog w(QString::number(count_to_reap) + " Plants reaped, Not enough space for all", "Info", this);
                w.exec();
            }
            else
            {
                MessageDialog w(QString::number(count_to_reap) + " Plants reaped", "Info", this);
                w.exec();
                if(current_place == WHEAT_FIELD)
                    emit WheatFieldReaped();
                else
                    emit AlfalfaFieldReaped();
            }

            field.reap(storage_place_id, count_to_reap);

            emit AddXP(field.reapXp());

            initialField(field);
        }
        else
        {
            QString err;
            if (current_place == WHEAT_FIELD)
                err = "You don't have enough space in your silo!";

            else if (current_place == ALFALFA_FIELD)
                err = "You don't have enough space in barn!";


            MessageDialog w(err, "Error", this);
            w.exec();
        }
    }
    else
    {
        MessageDialog w("Plants' growing is not finished yet!", "Error", this);
        w.exec();
    }
}

void DetailsDialog::on_btnUpgrade_clicked()
{
    if(!is_sound_muted)
        clickSound->play();
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
    if(!is_sound_muted)
        clickSound->play();
    switch (current_place)
    {
    case CHICKEN_COOP:
        if(farm.chicken_coop().animals_condition() == Enums::HUNGRY)
            feedLivingPlace(farm.chicken_coop());
        else
            collectLivingPlace(farm.chicken_coop());
        break;
    case COW_PASTURE:
        if(farm.cow_pasture().animals_condition() == Enums::HUNGRY)
            feedLivingPlace(farm.cow_pasture());
        else
            collectLivingPlace(farm.cow_pasture());
        break;
    case SHEEP_PASTURE:
        if(farm.sheep_pasture().animals_condition() == Enums::HUNGRY)
            feedLivingPlace(farm.sheep_pasture());
        else
            collectLivingPlace(farm.sheep_pasture());
        break;
    }
}

void DetailsDialog::on_btnPlant_clicked()
{
    if(!is_sound_muted)
        clickSound->play();
    MessageDialog dialog("Area you want to plant", "Input", this, true);
    connect(&dialog, &MessageDialog::entered_number, this, &DetailsDialog::on_plantAmountChoosed);

    switch (current_place)
    {
    case WHEAT_FIELD:
        if (farm.wheat_field().plants_condition() == Enums::NOT_PLANTED)
            dialog.exec();
        else if (farm.wheat_field().plants_condition() == Enums::REAPABLE)
            reapField(farm.wheat_field());
        break;

    case ALFALFA_FIELD:
        if (farm.alfalfa_field().plants_condition() == Enums::NOT_PLOWED)
            plowField(farm.alfalfa_field());
        else if (farm.alfalfa_field().plants_condition() == Enums::PLOWED)
            dialog.exec();
        else if (farm.alfalfa_field().plants_condition() == Enums::REAPABLE)
            reapField(farm.alfalfa_field());
        else if (farm.alfalfa_field().plants_condition() == Enums::PLOWING)
        {
            MessageDialog w("Plowing is not finished!", "Error", this);
            w.exec();
        }
        break;
    }
}

void DetailsDialog::on_plantAmountChoosed(int amount)
{
    if(current_place == WHEAT_FIELD)
        plantField(amount, farm.wheat_field());
    else if(current_place == ALFALFA_FIELD)
        plantField(amount, farm.alfalfa_field());
}

void DetailsDialog::initSounds()
{
    clickSound = new QSound("://sounds/clickSound.wav", this);
}

void DetailsDialog::disableUpgradeButton()
{
    ui->btnUpgrade->setCursor(Qt::ArrowCursor);
    ui->btnUpgrade->setStyleSheet("QPushButton{\n	border: none;\n	color: #fff;\n	background-image: url(:/img/upgrade-btn-disabled.png);\n}");
    ui->btnUpgrade->setEnabled(false);
}

void DetailsDialog::disableFeedCollectButton()
{
    btnFeedCollect->setStyleSheet("border: none;\n	border-radius: 10px;\n	background-color: #7d7d7d;\n	color: #fff;");
    btnFeedCollect->setEnabled(false);
}
