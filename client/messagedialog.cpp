#include "messagedialog.h"
#include "ui_messagedialog.h"

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
