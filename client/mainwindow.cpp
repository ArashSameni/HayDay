#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Farmer& farmer, Farm& farm, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), farmer(farmer), farm(farm)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
