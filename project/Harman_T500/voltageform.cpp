#include "voltageform.h"
#include "ui_voltageform.h"

VoltageForm::VoltageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VoltageForm)
{
    ui->setupUi(this);
}

VoltageForm::~VoltageForm()
{
    delete ui;
}
