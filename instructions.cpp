#include "instructions.h"
#include "ui_instructions.h"
#include "welcomepage.h"

Instructions::Instructions(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Instructions)
{
    ui->setupUi(this);
}

Instructions::~Instructions()
{
    delete ui;
}

void Instructions::on_pushButton_clicked()
{
    this->hide();
    welcomePage* welcome = new welcomePage(this);
    welcome->show();
}

