#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "globals.h"
#include "farmer.h"
#include "farm.h"
#include <QSound>
#include <qmediaplaylist.h>
#include <QMediaPlayer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Farmer& farmer, Farm& farm, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void anotherDayPassed();

    void on_btnSilo_clicked();

    void on_btnChickenCoop_clicked();

    void on_btnCowPasture_clicked();

    void on_btnSheepPasture_clicked();

    void on_chickenLock_clicked();

    void on_cowLock_clicked();

    void on_sheepLock_clicked();

    void on_btnBarn_clicked();

    void on_btnWheatField_clicked();

    void on_btnAlfalfaField_clicked();

    void on_alfalfaLock_clicked();

    void on_shopLock_clicked();

    void on_btnShop_clicked();

    void on_btnScoreBoard_clicked();

    void on_wheatFieldPlanted();
    void on_wheatFieldReaped();
    void on_alfalfaFieldPlanted();
    void on_alfalfaFieldReaped();

    void on_xp_add(int amount);
    void on_show_coin();

    void showChickens();
    void showCows();
    void showSheeps();

    void on_btnMute_clicked();

private:
    Ui::MainWindow *ui;
    Farmer& farmer;
    Farm& farm;
    QTimer* timer;
    QSound* clickSound;
    QMediaPlayer *music;

    void initUI();
    void initSounds();
    void checkTimeRelatedFunctions(bool add_day_xp);
    void showAnimals();
    void unlockAlfalfaField();
    void unlockChickenCoop();
    void unlockCowPasture();
    void unlockSheepPasture();
    void unlockShop();
    void showDay();
    void showCoin();
    void showXP();
    void showLevel();
};
#endif // MAINWINDOW_H
