#include "showdatabaseform.h"
#include "ui_showdatabaseform.h"

ShowDataBaseForm::ShowDataBaseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowDataBaseForm)
{
    ui->setupUi(this);
}

ShowDataBaseForm::~ShowDataBaseForm()
{
    delete ui;
}
