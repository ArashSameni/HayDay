#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    Farmer& farmer;
    Farm& farm;

    void initUI();
    void hideAnimals();
    void unlockAlfalfaField();
    void unlockChickenCoop();
    void unlockCowPasture();
    void unlockSheepPasture();
    void showChickens(int count);
    void showCows(int count);
    void showSheeps(int count);
};
#endif // MAINWINDOW_H
