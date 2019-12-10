#include "myform.h"
#include "ui_myform.h"

MyForm::MyForm(QWizardPage *parent) :
    QWizardPage(parent),
    ui(new Ui::MyForm)
{
    ui->setupUi(this);
}

MyForm::~MyForm()
{
    delete ui;
}
