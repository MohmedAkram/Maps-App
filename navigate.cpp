#include "navigate.h"
#include "ui_navigate.h"
#include "welcomepage.h"
#include "graphitem.h"

Navigate::Navigate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Navigate)
{
    ui->setupUi(this);
    ui->errorlabel->setVisible(false);
    ui->errorlabel_2->setVisible(false);
    ui->theShortest->setVisible(false);
    // ui->city1->setVisible(false);
    // ui->andlabel->setVisible(false);
    // ui->city2->setVisible(false);
    // ui->is->setVisible(false);
    // ui->distance->setVisible(false);
    // ui->km->setVisible(false);
    ui->thePath->setVisible(false);
    ui->path->setVisible(false);
    // ui->last->setVisible(false);

    ui->sourcebox->addItem("");
    ui->sourcebox->setCurrentIndex(0);

    ui->destinationbox->addItem("");
    ui->destinationbox->setCurrentIndex(0);

    for (const auto& cities : graph.adjList)
    {
        ui->sourcebox->addItem(cities.first);
    }

    for (const auto& cities : graph.adjList)
    {
        ui->destinationbox->addItem(cities.first);
    }

}

Navigate::~Navigate()
{
    delete ui;
}

void Navigate::on_back_clicked()
{
    this->hide();
    welcomePage* welcome = new welcomePage(this);
    welcome->show();
}


void Navigate::on_go_clicked()
{

    if (ui->sourcebox->currentText() == "" || ui->destinationbox->currentText() == "")
    {
        ui->errorlabel_2->setVisible(true);
        ui->errorlabel->setVisible(false);

    }
    else if (ui->sourcebox->currentText() == ui->destinationbox->currentText())
    {
        ui->errorlabel_2->setVisible(false);
        ui->errorlabel->setVisible(true);
    }
    else
    {

        location = ui->sourcebox->currentText();
        destination = ui->destinationbox->currentText();
        pair<vector<QString>, float> path = graph.FindShortestDis(location, destination);
        ui->theShortest->setText("The shortest distance between " + location + " and " + destination + " is " + QString::number(path.second) + " km.");
        // ui->city1->setText(location);
        // ui->city2->setText(destination);
        // ui->distance->setText(QString::number(path.second));
        ui->theShortest->setVisible(true);
        // ui->city1->setVisible(true);
        // ui->andlabel->setVisible(true);
        // ui->city2->setVisible(true);
        // ui->is->setVisible(true);
        // ui->distance->setVisible(true);
        // ui->km->setVisible(true);
        ui->errorlabel_2->setVisible(false);
        ui->errorlabel->setVisible(false);
        QString navigation;
        for (const auto& city : path.first)
        {
            navigation += city +" --> ";

        }
        // ui->last->setText(destination);
        ui->path->setText(navigation + destination);
        ui->thePath->setVisible(true);
        ui->path->setVisible(true);
        // ui->last->setVisible(true);

    }
}

