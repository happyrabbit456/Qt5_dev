#include "versionform.h"
#include "ui_versionform.h"

VersionForm::VersionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VersionForm)
{
    ui->setupUi(this);
}

VersionForm::~VersionForm()
{
    delete ui;
}
