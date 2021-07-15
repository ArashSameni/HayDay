#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "detailsdialog.h"

MainWindow::MainWindow(Farmer& farmer, Farm& farm, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), farmer(farmer), farm(farm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    initUI();

    //Connect Timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::anotherDayPassed);
    timer->start(static_cast<int>(SECONDS_PER_DAY) * 1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::anotherDayPassed()
{
    CURRENT_DAY += 1;
    int xp_to_add = 1;

    if(farm.silo().is_upgrading() && farm.silo().isUpgradeFinished())
    {
        farm.silo().finishUpgrade();
        xp_to_add += farm.silo().upgradeXp();
    }
    if(farm.barn().is_upgrading() && farm.barn().isUpgradeFinished())
    {
        farm.barn().finishUpgrade();
        xp_to_add += farm.barn().upgradeXp();
    }
    if(farm.chicken_coop().is_upgrading() && farm.chicken_coop().isUpgradeFinished())
    {
        farm.chicken_coop().finishUpgrade();
        xp_to_add += farm.chicken_coop().upgradeXp();
    }
    if(farm.cow_pasture().is_upgrading() && farm.cow_pasture().isUpgradeFinished())
    {
        farm.cow_pasture().finishUpgrade();
        xp_to_add += farm.cow_pasture().upgradeXp();
    }
    if(farm.sheep_pasture().is_upgrading() && farm.sheep_pasture().isUpgradeFinished())
    {
        farm.sheep_pasture().finishUpgrade();
        xp_to_add += farm.sheep_pasture().upgradeXp();
    }
    if(farm.alfalfa_field().is_upgrading() && farm.alfalfa_field().isUpgradeFinished())
    {
        farm.alfalfa_field().finishUpgrade();
        xp_to_add += farm.alfalfa_field().upgradeXp();
    }
    if(farm.wheat_field().is_upgrading() && farm.wheat_field().isUpgradeFinished())
    {
        farm.wheat_field().finishUpgrade();
        xp_to_add += farm.wheat_field().upgradeXp();
    }

    if(farmer.addXpAndIsLevelFinished(xp_to_add))
    {
        //farmer.goNextLevel();
        showLevel();
    }
    showXP();
    showDay();
    farmer.save();
}

void MainWindow::initUI()
{
    showCoin();
    showDay();
    showLevel();
    showXP();
    showAnimals();
}

void MainWindow::showAnimals()
{
    if(farm.chicken_coop().storage() > 0)
        unlockChickenCoop();
    if(farm.cow_pasture().storage() > 0)
        unlockCowPasture();
    if(farm.sheep_pasture().storage() > 0)
        unlockSheepPasture();

    showChickens(farm.chicken_coop().storage());
    showCows(farm.cow_pasture().storage());
    showSheeps(farm.cow_pasture().storage());
}

void MainWindow::unlockAlfalfaField()
{
    ui->alfalfaLock->deleteLater();
    ui->btnAlfalfaField->setEnabled(true);
    ui->btnAlfalfaField->setCursor(Qt::PointingHandCursor);
    //Change picture from dark to light on focus
    ui->btnAlfalfaField->setStyleSheet("QPushButton{\n	border: none;\n	background-image: url(:/img/field-dark.png);\n}\n\nQPushButton:hover{\n	background-image: url(:/img/field.png);\n}");
}

void MainWindow::unlockChickenCoop()
{
    ui->chickenLock->deleteLater();
    ui->btnChickenCoop->setEnabled(true);
    ui->btnChickenCoop->setCursor(Qt::PointingHandCursor);
    //Change picture from dark to light on focus
    ui->btnChickenCoop->setStyleSheet("QPushButton{\n	border: none;\n	background-image: url(:/img/chicken_coop-dark.png);\n}\n\nQPushButton:hover{\n	background-image: url(:/img/chicken_coop.png);\n}");
}

void MainWindow::unlockCowPasture()
{
    ui->cowLock->deleteLater();
    ui->btnCowPasture->setEnabled(true);
    ui->btnCowPasture->setCursor(Qt::PointingHandCursor);
    //Change picture from dark to light on focus
    ui->btnSheepPasture->setStyleSheet("QPushButton{\n	border: none;\n	background-image: url(:/img/pasture-dark.png);\n}\n\nQPushButton:hover{\n	background-image: url(:/img/pasture.png);\n}");
}

void MainWindow::unlockSheepPasture()
{
    ui->sheepLock->deleteLater();
    ui->btnSheepPasture->setEnabled(true);
    ui->btnSheepPasture->setCursor(Qt::PointingHandCursor);
    //Change picture from dark to light on focus
    ui->btnSheepPasture->setStyleSheet("QPushButton{\n	border: none;\n	background-image: url(:/img/pasture-dark.png);\n}\n\nQPushButton:hover{\n	background-image: url(:/img/pasture.png);\n}");
}

void MainWindow::showChickens(int count)
{
    ui->btnChicken_1->setVisible(false);
    ui->btnChicken_2->setVisible(false);
    ui->btnChicken_3->setVisible(false);
    ui->btnChicken_4->setVisible(false);
    ui->btnChicken_5->setVisible(false);
    ui->btnChicken_6->setVisible(false);

    if(count >= 1)
        ui->btnChicken_1->setVisible(true);
    if(count >= 2)
        ui->btnChicken_2->setVisible(true);
    if(count >= 3)
        ui->btnChicken_3->setVisible(true);
    if(count >= 4)
        ui->btnChicken_4->setVisible(true);
    if(count >= 5)
        ui->btnChicken_5->setVisible(true);
    if(count >= 6)
        ui->btnChicken_6->setVisible(true);
}

void MainWindow::showCows(int count)
{
    ui->btnCow_1->setVisible(false);
    ui->btnCow_2->setVisible(false);
    ui->btnCow_3->setVisible(false);
    ui->btnCow_4->setVisible(false);

    if(count >= 1)
        ui->btnCow_1->setVisible(true);
    if(count >= 2)
        ui->btnCow_2->setVisible(true);
    if(count >= 3)
        ui->btnCow_3->setVisible(true);
    if(count >= 4)
        ui->btnCow_4->setVisible(true);
}

void MainWindow::showSheeps(int count)
{
    ui->btnSheep_1->setVisible(false);
    ui->btnSheep_2->setVisible(false);
    ui->btnSheep_3->setVisible(false);
    ui->btnSheep_4->setVisible(false);
    ui->btnSheep_5->setVisible(false);
    ui->btnSheep_6->setVisible(false);

    if(count >= 1)
        ui->btnSheep_1->setVisible(true);
    if(count >= 2)
        ui->btnSheep_2->setVisible(true);
    if(count >= 3)
        ui->btnSheep_3->setVisible(true);
    if(count >= 4)
        ui->btnSheep_4->setVisible(true);
    if(count >= 5)
        ui->btnSheep_5->setVisible(true);
    if(count >= 6)
        ui->btnSheep_6->setVisible(true);
}

void MainWindow::showDay()
{
    ui->lblDay->setNum(static_cast<int>(CURRENT_DAY));
}

void MainWindow::showCoin()
{
    ui->lblCoin->setNum(farmer.coins());
}

void MainWindow::showXP()
{
    ui->lblXP->setText(QString::number(farmer.xp()) + " / " + QString::number(farmer.max_xp()));

    if(farmer.xp())
        ui->pbar_left_corner->setVisible(true);
    else
        ui->pbar_left_corner->setVisible(false);

    if(farmer.xp() > 1)
    {
        const int progress = static_cast<int>((static_cast<float>(farmer.xp()) / farmer.max_xp()) * 100);
        const int width_of_center_pbar = 196;
        ui->pbar_center->resize(width_of_center_pbar * (progress - 1) / 98, 20);
        ui->pbar_center->setVisible(true);
    }
    else
        ui->pbar_center->setVisible(false);
}

void MainWindow::showLevel()
{
    ui->lblLevel->setText(QString::number(farmer.level()));
}

void MainWindow::on_btnSilo_clicked()
{
    DetailsDialog details("Silo", farmer, farm, this);
    details.exec();
}
