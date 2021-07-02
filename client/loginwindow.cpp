#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);

    ui->gboxSignup->setVisible(false);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_lblSignup_clicked()
{
    ui->gboxLogin->setVisible(false);
    ui->gboxSignup->setVisible(true);
}

void LoginWindow::on_lblLogin_clicked()
{
    ui->gboxSignup->setVisible(false);
    ui->gboxLogin->setVisible(true);
}
