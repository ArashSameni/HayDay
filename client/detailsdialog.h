#ifndef DETAILSDIALOG_H
#define DETAILSDIALOG_H

#include <QDialog>
#include "farmer.h"
#include "farm.h"

namespace Ui {
class DetailsDialog;
}

class DetailsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DetailsDialog(QString title, Farmer& farmer, Farm& farm, QWidget *parent = nullptr);
    ~DetailsDialog();

private slots:
    void on_btnUpgrade_clicked();

private:
    enum
    {
        SILO,

    };

    Ui::DetailsDialog *ui;
    Farmer& farmer;
    Farm& farm;
    int current_place;
    void initialByPlace(const Place& place);
    void initialSilo();
    void upgradeSilo();
};

#endif // DETAILSDIALOG_H
