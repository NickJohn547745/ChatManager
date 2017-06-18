#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gframe.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gYTUsername->setHeaderText("Enter E-mail:");
    ui->gYTUsername->setColor(QColor(229, 45, 39));

    ui->gYTPassword->setHeaderText("Enter Password:");
    ui->gYTPassword->setColor(QColor(229, 45, 39));
    ui->gYTPassword->setPasswordMode(true);
    ui->gYTPassword->showError("No Password Provided");

    ui->gTWUsername->setHeaderText("Enter E-mail:");
    ui->gTWUsername->setColor(QColor(100, 65, 164));

    ui->gTWPassword->setHeaderText("Enter Password:");
    ui->gTWPassword->setColor(QColor(100, 65, 164));
    ui->gTWPassword->setPasswordMode(true);
    ui->gTWPassword->showError("No Password Provided");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *e)
{

}
