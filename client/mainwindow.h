#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "globals.h"
#include "farmer.h"
#include "farm.h"

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

private:
    Ui::MainWindow *ui;
    Farmer& farmer;
    Farm& farm;
    QTimer* timer;

    void initUI();
    void showAnimals();
    void unlockAlfalfaField();
    void unlockChickenCoop();
    void unlockCowPasture();
    void unlockSheepPasture();
    void showChickens(int count);
    void showCows(int count);
    void showSheeps(int count);
    void showDay();
    void showCoin();
    void showXP();
    void showLevel();
};
#endif // MAINWINDOW_H
