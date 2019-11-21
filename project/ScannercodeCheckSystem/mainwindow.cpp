#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Logo图片显示
//    ui->labelLogo->clear();
//    ui->labelLogo->setPixmap(QPixmap(":/res/images/MINAMI_logo.jpg"));
//    ui->labelLogo->setScaledContents(true);
//    ui->labelLogo->show();


    m_pTestForm=new TestForm();
    m_pShowDataForm=new ShowDataBaseForm();
    m_pVersionForm=new VersionForm();

    ui->tabWidget->insertTab(0,m_pTestForm,tr("Test"));
    ui->tabWidget->insertTab(1,m_pShowDataForm,tr("ShowDatabase"));
    ui->tabWidget->insertTab(2,m_pVersionForm,"ReviseHistory");

    ui->lineEditDuration->setText("00:00:00");
    SetCurrDateTime();

    m_timer.start(1000,  this);
}

MainWindow::~MainWindow()
{
    m_timer.stop();

    delete m_pTestForm;
    delete m_pShowDataForm;
    delete m_pVersionForm;

    delete ui;
}


void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timer.timerId()) {
        SetCurrDateTime();

        update();
    } else {
        QWidget::timerEvent(event);
    }
}

void MainWindow::SetCurrDateTime()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    //QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    QString date = current_date_time.toString("yyyy.MM.dd");
//        qDebug()<<date;
    ui->lineEditDate->setText(date);
    QString time = current_date_time.toString("hh:mm:ss");
//        qDebug()<<time;
    ui->lineEditTime->setText(time);
}

