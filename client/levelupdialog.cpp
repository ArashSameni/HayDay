#include "levelupdialog.h"
#include "ui_levelupdialog.h"

LevelUpDialog::LevelUpDialog(int level ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LevelUpDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    lblLeft = new QLabel(this);
    lblRight = new QLabel(this);
    levelUpSound=new QSound("://sounds/levelUpSound.wav", this);
    if(!is_sound_muted)
        levelUpSound->play();
    ui->lblCongrates->setText("Congratulations, You are now a level " + QString::number(level) + " farmer!!");
    if(level ==5 || level > 6)
        ui->lblCongrates->setGeometry(0,180,450,32);
    showUnlocks(level);
}

void LevelUpDialog::showUnlocks(int lvl)
{
    switch(lvl)
    {
    case 2:
        showChickenUnlocks();
        break;
    case 3:
        showAlfafaUnlocks();
        break;
    case 4:
        showCowUnlocks();
        break;
    case 6:
        showSheepUnlocks();
        break;
    }
}

void LevelUpDialog::showChickenUnlocks()
{
    lblLeft->setAlignment(Qt::AlignCenter);
    lblLeft->setGeometry(110, 175 , 92 , 92);
    lblLeft->setStyleSheet("background-image: url(:/img/chicken-lbl.png);");

    lblRight->setAlignment(Qt::AlignCenter);
    lblRight->setGeometry(240, 184 , 88 , 80);
    lblRight->setStyleSheet("background-image: url(:/img/egg-lbl.png);");
}

void LevelUpDialog::showAlfafaUnlocks()
{
    lblLeft->setAlignment(Qt::AlignCenter);
    lblLeft->setGeometry(170, 184, 88 , 92);
    lblLeft->setStyleSheet("background-image: url(:/img/alfalfa-lbl.png);");
}

void LevelUpDialog::showCowUnlocks()
{

    lblLeft->setAlignment(Qt::AlignCenter);
    lblLeft->setGeometry(110, 175 , 98 , 94);
    lblLeft->setStyleSheet("background-image: url(:/img/cow-lbl.png);");

    lblRight->setAlignment(Qt::AlignCenter);
    lblRight->setGeometry(260, 175 , 39 , 92);
    lblRight->setStyleSheet("background-image: url(:/img/milk-lbl.png);");

}

void LevelUpDialog::showSheepUnlocks()
{

    lblLeft->setAlignment(Qt::AlignCenter);
    lblLeft->setGeometry(110, 175 , 85 , 89);
    lblLeft->setStyleSheet("background-image: url(:/img/sheep-lbl.png);");

    lblRight->setAlignment(Qt::AlignCenter);
    lblRight->setGeometry(230, 175 , 82 , 92);
    lblRight->setStyleSheet("background-image: url(:/img/wool-lbl.png);");
}



LevelUpDialog::~LevelUpDialog()
{
    delete ui;
}

void LevelUpDialog::on_btnContinue_clicked()
{
    this->close();
}
