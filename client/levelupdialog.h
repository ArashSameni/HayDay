#ifndef LEVELUPDIALOG_H
#define LEVELUPDIALOG_H
#include <vector>
#include <QDialog>
#include <QLabel>
#include <QSound>
#include "globals.h"
namespace Ui {
class LevelUpDialog;
}

class LevelUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LevelUpDialog(int level , QWidget *parent = nullptr);
    void showUnlocks(int lvl);
    void showChickenUnlocks();
    void showAlfafaUnlocks();
    void showCowUnlocks();
    void showSheepUnlocks();
    ~LevelUpDialog();

private slots:
    void on_btnContinue_clicked();

private:
    QSound* levelUpSound;
    Ui::LevelUpDialog *ui;
    QLabel* lblLeft;
    QLabel* lblRight;
};

#endif // LEVELUPDIALOG_H
