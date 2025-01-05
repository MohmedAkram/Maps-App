#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "welcomepage.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->errorlabel->setVisible(false);

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{


}

void MainWindow::on_start_clicked()
{
    if (ui->Name->text().isEmpty())
        ui->errorlabel->setVisible(true);
    else
    {
        this->hide();
        welcomePage* welcome = new welcomePage(this);
        welcome->setName(ui->Name->text());
        welcome->show();
    }
}


void MainWindow::on_quit_clicked()
{
    QApplication::quit();

}

