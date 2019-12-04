#include "currentform.h"
#include "ui_currentform.h"

CurrentForm::CurrentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentForm)
{
    ui->setupUi(this);
}

CurrentForm::~CurrentForm()
{
    delete ui;
}
