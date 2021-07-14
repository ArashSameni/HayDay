#include "barndetailsdialog.h"
#include "ui_barndetailsdialog.h"

BarnDetailsDialog::BarnDetailsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BarnDetailsDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    initUI();
}

BarnDetailsDialog::~BarnDetailsDialog()
{
    delete ui;
}

void BarnDetailsDialog::on_lblUpgrade_clicked()
{
    if(isBarnShown)
        showUpgrade();
    else
        showBarn();

    isBarnShown = !isBarnShown;
}

void BarnDetailsDialog::initUI()
{
    showBarn();
}

void BarnDetailsDialog::showUpgrade()
{
    this->setStyleSheet("*{\n	font: 24px \"IRANSans Light\";\n	color: #494949;\n}\n\nQDialog { background-image: url(:/img/details-bg.png) }");

    ui->lblEgg->hide();
    ui->lblMilk->hide();
    ui->lblNail->hide();
    ui->lblWool->hide();
    ui->lblShovel->hide();
    ui->lblAlfalfa->hide();

    ui->lblUpgrade->setText("> Details");

    ui->lblUpgradeShovel->show();
    ui->lblUpgradeNail->show();
    ui->lblUpgradeTime->show();
    ui->btnUpgrade->show();
    ui->lblUpgradeInfo->show();
    ui->lblDaysLeft->show();

}

void BarnDetailsDialog::showBarn()
{
    this->setStyleSheet("*{\n	font: 24px \"IRANSans Light\";\n	color: #494949;\n}\n\nQDialog { background-image: url(:/img/barn-bg.png) }");

    ui->lblEgg->show();
    ui->lblMilk->show();
    ui->lblNail->show();
    ui->lblWool->show();
    ui->lblShovel->show();
    ui->lblAlfalfa->show();

    ui->lblUpgrade->setText("> Upgrade");

    ui->lblUpgradeShovel->hide();
    ui->lblUpgradeNail->hide();
    ui->lblUpgradeTime->hide();
    ui->btnUpgrade->hide();
    ui->lblUpgradeInfo->hide();
    ui->lblDaysLeft->hide();
}
