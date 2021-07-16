#include "messagedialog.h"
#include "ui_messagedialog.h"

MessageDialog::MessageDialog(QString text, QString title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageDialog)
{
    ui->setupUi(this);
    setWindowTitle(title);
    ui->lblMessage->setText(text);
}

MessageDialog::~MessageDialog()
{
    delete ui;
}

void MessageDialog::on_btnOk_clicked()
{
    this->close();
}
