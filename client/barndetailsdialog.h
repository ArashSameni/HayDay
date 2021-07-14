#ifndef BARNDETAILSDIALOG_H
#define BARNDETAILSDIALOG_H

#include <QDialog>

namespace Ui {
class BarnDetailsDialog;
}

class BarnDetailsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BarnDetailsDialog(QWidget *parent = nullptr);
    ~BarnDetailsDialog();

private slots:
    void on_lblUpgrade_clicked();

private:
    Ui::BarnDetailsDialog *ui;
    bool isBarnShown = true;

    void initUI();
    void showUpgrade();
    void showBarn();
};

#endif // BARNDETAILSDIALOG_H
