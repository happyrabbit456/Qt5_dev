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
    m_pDatabaseForm=new DatabaseForm(this);
    ui->tabCurrentWidget->insertTab(0,m_pTestForm,tr("Test"));
    ui->tabCurrentWidget->insertTab(1,m_pParameterForm,tr("Parameter"));
    ui->tabCurrentWidget->insertTab(2,m_pDatabaseForm,tr("Database"));
    ui->tabCurrentWidget->setCurrentIndex(0);

    connect(m_pTestForm, SIGNAL(updateDatabaseTabelView()),m_pDatabaseForm, SLOT(updateTableView()));
}

CurrentForm::~CurrentForm()
{
    delete ui;
}








