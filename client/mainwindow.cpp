#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Farmer& farmer, Farm& farm, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), farmer(farmer), farm(farm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    hideAnimals();
}

void MainWindow::hideAnimals()
{
    //Hide chickens
    ui->btnChicken_1->setVisible(false);
    ui->btnChicken_2->setVisible(false);
    ui->btnChicken_3->setVisible(false);
    ui->btnChicken_4->setVisible(false);
    ui->btnChicken_5->setVisible(false);
    ui->btnChicken_6->setVisible(false);

    //Hide cows
    ui->btnCow_1->setVisible(false);
    ui->btnCow_2->setVisible(false);
    ui->btnCow_3->setVisible(false);
    ui->btnCow_4->setVisible(false);

    //Hide sheeps
    ui->btnSheep_1->setVisible(false);
    ui->btnSheep_2->setVisible(false);
    ui->btnSheep_3->setVisible(false);
    ui->btnSheep_4->setVisible(false);
    ui->btnSheep_5->setVisible(false);
    ui->btnSheep_6->setVisible(false);
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

void MainWindow::showSheep(int count)
{
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
