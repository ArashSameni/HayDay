#include "messagedialog.h"
#include "ui_messagedialog.h"
#include "globals.h"

MessageDialog::MessageDialog(QString text, QString title, QWidget *parent, bool get_num) :
    QDialog(parent),
    ui(new Ui::MessageDialog)
{
    ui->setupUi(this);
    setWindowTitle(title);
    ui->lblMessage->setText(text);
    if(!get_num)
    {
        ui->txtNumber->hide();
        setFixedSize(450, 140);
    }

    if(title == "Error" && !is_sound_muted)
    {
        errorSound = new QSound("://sounds/error.wav", this);
        errorSound->play();
    }
}

MessageDialog::~MessageDialog()
{
    delete ui;
}

void MessageDialog::on_btnOk_clicked()
{
    emit entered_number(ui->txtNumber->value());
    this->close();
}
