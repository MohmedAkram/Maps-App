#include "welcomepage.h"
#include "ui_welcomepage.h"
#include "cities.h"
#include "paths.h"
#include "navigate.h"
#include "instructions.h"
#include "graphitem.h"
#include <QApplication>

welcomePage::welcomePage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::welcomePage)
{
    ui->setupUi(this);
}

welcomePage::~welcomePage()
{
    delete ui;
}

// void welcomePage::setName(QString name)
// {
//     ui->name->setText(name);
//     ui->name->adjustSize();
//     ui->name->setFixedHeight(51);
// }

void welcomePage::on_cities_clicked()
{
    this->hide();
    Cities* manageCities = new Cities(this);
    manageCities->show();
}


void welcomePage::on_paths_clicked()
{
    this->hide();
    Paths* managePaths = new Paths(this);
    managePaths->show();
}


void welcomePage::on_navigate_clicked()
{
    this->hide();
    Navigate* navigation = new Navigate(this);
    navigation->show();
}


void welcomePage::on_quit_clicked()
{
    graph.WriteToFile("C:\\Users\\mahin\\Desktop\\Uni\\Spring 2024\\CS 2 Lab\\Lab Project\\Current\\CS2-Lab-Project\\MiniWasalnyApp\\Cities.txt");
    QApplication::quit();
}


void welcomePage::on_pushButton_5_clicked()
{
    this->hide();
    Instructions* help = new Instructions(this);
    help->show();
}

