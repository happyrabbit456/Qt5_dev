#include "currentform.h"
#include "ui_currentform.h"

#include "mainwindow.h"

CurrentForm::CurrentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentForm)
{
    ui->setupUi(this);

    m_pTestForm=new TestForm(this);
    m_pParameterForm=new ParameterForm(this);
    ui->tabCurrentWidget->insertTab(0,m_pTestForm,tr("Test"));
    ui->tabCurrentWidget->insertTab(1,m_pParameterForm,tr("ParameterSetting"));
    ui->tabCurrentWidget->setCurrentIndex(0);
}

CurrentForm::~CurrentForm()
{
    delete ui;
}








