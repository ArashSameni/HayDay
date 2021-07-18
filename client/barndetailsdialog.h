#ifndef BARNDETAILSDIALOG_H
#define BARNDETAILSDIALOG_H

#include "farmer.h"
#include "farm.h"
#include "barn.h"
#include <QDialog>
#include <QSound>

namespace Ui {
class BarnDetailsDialog;
}

class BarnDetailsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BarnDetailsDialog(Farmer& farmer, Farm& farm, QWidget *parent = nullptr);
    ~BarnDetailsDialog();

private slots:
    void on_lblUpgrade_clicked();

    void on_btnUpgrade_clicked();

signals:
    void ShowCoin();

private:
    Ui::BarnDetailsDialog *ui;
    bool isBarnShown = true;
    Farmer &farmer;
    Farm &farm;
    QSound* clickSound;

    void initUI();
    void initSounds();
    void initUpgrade();
    void initBarn();
    void showUpgrade();
    void showBarn();
    void upgradeBarn();
};

#endif // BARNDETAILSDIALOG_H
