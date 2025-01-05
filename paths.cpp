#include "paths.h"
#include "ui_paths.h"
#include "welcomepage.h"
#include "graphitem.h"


Paths::Paths(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Paths)
{
    ui->setupUi(this);
    ui->frame->hide();
    ui->errorlabel->setVisible(false);
    ui->errorlabel_2->setVisible(false);

    for (const auto& cities : graph.adjList)
    {
        ui->sourcebox->addItem(cities.first);
    }

    for (const auto& cities : graph.adjList)
    {
        ui->destbox->addItem(cities.first);
    }

}

Paths::~Paths()
{
    delete ui;
}

void Paths::on_back_clicked()
{
    this->hide();
    welcomePage* welcome = new welcomePage(this);
    welcome->show();
}


void Paths::on_addpath_clicked()
{
    ui->addpath->setEnabled(false);
    ui->modifypath->setEnabled(false);
    ui->deletepath->setEnabled(false);
    ui->frame->show();
    ui->newdistlabel->setVisible(false);
    ui->delete1->setVisible(false);
    ui->delete1->setEnabled(false);
    ui->modify->setVisible(false);
    ui->modify->setEnabled(false);
    ui->enterdistlabel->setVisible(true);
    ui->distedit->setVisible(true);
    ui->add->setEnabled(true);
    ui->add->setVisible(true);

}


void Paths::on_modifypath_clicked()
{
    ui->addpath->setEnabled(false);
    ui->modifypath->setEnabled(false);
    ui->deletepath->setEnabled(false);
    ui->frame->show();
    ui->enterdistlabel->setVisible(false);
    ui->delete1->setVisible(false);
    ui->delete1->setEnabled(false);
    ui->add->setVisible(false);
    ui->add->setEnabled(false);
    ui->newdistlabel->setVisible(true);
    ui->distedit->setVisible(true);
    ui->modify->setEnabled(true);
    ui->modify->setVisible(true);
}


void Paths::on_deletepath_clicked()
{
    ui->addpath->setEnabled(false);
    ui->modifypath->setEnabled(false);
    ui->deletepath->setEnabled(false);
    ui->frame->show();
    ui->enterdistlabel->setVisible(false);
    ui->newdistlabel->setVisible(false);
    ui->distedit->setVisible(false);
    ui->add->setVisible(false);
    ui->add->setEnabled(false);
    ui->modify->setVisible(false);
    ui->modify->setEnabled(false);
    ui->delete1->setEnabled(true);
    ui->delete1->setVisible(true);

}


void Paths::on_cancel_clicked()
{
    ui->frame->hide();
    ui->addpath->setEnabled(true);
    ui->modifypath->setEnabled(true);
    ui->deletepath->setEnabled(true);
    ui->errorlabel->setVisible(false);
    ui->errorlabel_2->setVisible(false);

}
void Paths::on_delete1_clicked()
{
    QString city1 = ui->sourcebox->currentText();
    QString city2 = ui->destbox->currentText();
    graph.removeEdge(city1,city2);
    QMessageBox::information(this, "Success","Path removed successfully between " + city1 + " and " + city2 + ".");
    ui->sourcebox->setCurrentIndex(0);
    ui->destbox->setCurrentIndex(0);

}


void Paths::on_add_clicked()
{
    QString city1 = ui->sourcebox->currentText();
    QString city2 = ui->destbox->currentText();
    QString distance = ui->distedit->text();
    bool yes=true;
    float distance_float= distance.toFloat(&yes);

    if (ui->distedit->text().isEmpty())
    {
        ui->errorlabel->setText("Please choose two cities and enter a distance");
        ui->errorlabel->setVisible(true);
    }
    else if (graph.edgeExists(city1, city2))
    {
        ui->errorlabel->setText("Path already exists!");
        ui->errorlabel->setVisible(true);
    }
    else
    {
        graph.AddEdge(city1,city2,distance_float);
        QMessageBox::information(this, "Success", "Distance " + distance+ " km added successfully between " + city1 + " and " + city2 + ".");
        ui->errorlabel->setVisible(false);
        ui->sourcebox->setCurrentIndex(0);
        ui->destbox->setCurrentIndex(0);

    }

}


void Paths::on_modify_clicked()
{
    QString city1 = ui->sourcebox->currentText();
    QString city2 = ui->destbox->currentText();
    QString distance = ui->distedit->text();
    bool yes = true;
    float distance_float= distance.toFloat(&yes);

    if (ui->distedit->text().isEmpty())
    {
        ui->errorlabel->setText("Please select two cities and enter a new distance");
        ui->errorlabel->setVisible(true);
    }
    else if (!graph.edgeExists(city1, city2))
    {
        ui->errorlabel->setText("Path does not exist");
        ui->errorlabel->setVisible(true);
    }
    else
    {
        graph.UpdateGraph(city1,city2,distance_float);
        QMessageBox::information(this, "Success", "Distance updated successfully between " + city1 + " and " + city2 + " to " + distance +"km.");
        ui->errorlabel->setVisible(false);
        ui->sourcebox->setCurrentIndex(0);
        ui->destbox->setCurrentIndex(0);

    }
}

