#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Logo图片显示
//    ui->labelLogo->setPixmap(QPixmap(":/res/images/MINAMI_logo.jpg"));
//    ui->labelLogo->show();
//    ui->labelLogo->setScaledContents(true);

    m_pTestForm=new TestForm();
    m_pShowDataForm=new ShowDataBaseForm();
    m_pVersionForm=new VersionForm();



    ui->tabWidget->insertTab(0,m_pTestForm,tr("Test"));
    ui->tabWidget->insertTab(1,m_pShowDataForm,tr("ShowDatabase"));
    ui->tabWidget->insertTab(2,m_pVersionForm,"ReviseHistory");
}

MainWindow::~MainWindow()
{
    delete ui;

    delete m_pTestForm;
    delete m_pShowDataForm;
    delete m_pVersionForm;
}

