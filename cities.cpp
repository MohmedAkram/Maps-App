#include "cities.h"
#include "ui_cities.h"
#include "welcomepage.h"
#include "graphitem.h"

Cities::Cities(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Cities)
{
    ui->setupUi(this);
    ui->frame->hide();
    ui->status->setVisible(false);

    for (const auto& cities : graph.adjList)
    {
        ui->comboBox->addItem(cities.first);
    }
}

Cities::~Cities()
{
    delete ui;
}

void Cities::on_back_clicked()
{
    this->hide();
    welcomePage* welcome = new welcomePage(this);
    welcome->show();
}



void Cities::on_addcity_clicked()
{
    ui->addcity->setEnabled(false);
    ui->deletecity->setEnabled(false);
    ui->frame->show();
    ui->choosecity->hide();
    ui->comboBox->hide();
    ui->delete1->hide();
    ui->delete1->setEnabled(false);
    ui->add->show();
    ui->add->setEnabled(true);
    ui->entername->show();
    ui->nameEdit->show();

}


void Cities::on_deletecity_clicked()
{
    ui->addcity->setEnabled(false);
    ui->deletecity->setEnabled(false);
    ui->frame->show();
    ui->choosecity->show();
    ui->comboBox->show();
    ui->delete1->show();
    ui->delete1->setEnabled(true);
    ui->add->hide();
    ui->add->setEnabled(false);
    ui->entername->hide();
    ui->nameEdit->hide();

}

void Cities::on_cancel_clicked()
{
    ui->addcity->setEnabled(true);
    ui->deletecity->setEnabled(true);
    ui->frame->hide();
    ui->status->setVisible(false);

}


void Cities::on_delete1_clicked()
{
    if (ui->comboBox->currentText().isEmpty())
    {
        ui->status->setText("Please select a city above");
        ui->status->setVisible(true);
    }
    else
    {
        QString cityname = ui->comboBox->currentText(); //gets selected city from combo box
        graph.DeleteCity(cityname); //deletes city from graph
        ui->comboBox->removeItem(ui->comboBox->findText(cityname)); //deletes city from combo box
        ui->comboBox->setCurrentIndex(0);
        ui->status->setText(cityname + " deleted successfully");
        ui->status->setVisible(true);
    }
}

void Cities::on_add_clicked()
{
    if (ui->nameEdit->text().isEmpty())
    {
        ui->status->setText("Please enter a city above");
        ui->status->setVisible(true);
    }
    else
    {
        QString cityname = ui->nameEdit->text();

        if (graph.cityExists(cityname))
        {
            ui->status->setText(cityname + " already exists");
            ui->status->setVisible(true);
            ui->nameEdit->clear();
        }
        else
        {
            graph.AddCity(cityname); //add city to graph
            ui->comboBox->addItem(cityname); //add city to combo box
            ui->status->setText(cityname + " added successfully");
            ui->status->setVisible(true);
            ui->nameEdit->clear();
        }

    }

}

