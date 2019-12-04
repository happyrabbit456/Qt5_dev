#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <exception>

#include <QDebug>
#include <QStringListModel>

/*
 * https://blog.csdn.net/lmylikefx/article/details/74926447
 * Vs2010写的通过gpib调用visa库控制安捷伦电源66309 d的代码，这段代码是读取一段电流波形的平均值，最大值，最小值等，适用于模块的功率测试。
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);   

//    GPIB gpib;
//    gpib.sample();

//    double value = 0.0;
//    gpib.DMM_ReadCurrent(value);

    m_pCurrentForm=new CurrentForm(this);
    ui->stackedWidget->addWidget(m_pCurrentForm);
    ui->stackedWidget->setCurrentIndex(0);

    SetCurrDateTime();

    m_timer.start(1000,  this);

    QStringListModel* slm = new QStringListModel(this);
    QStringList* sl = new QStringList();
    sl->append("Current");
    sl->append("Voltage");
    slm->setStringList(*sl);
    ui->listViewSelector->setModel(slm);
    delete sl;

    QModelIndex index = slm->index(Selector_Current);
    ui->listViewSelector->setCurrentIndex(index);
}

MainWindow::~MainWindow()
{
    delete ui;

    if(m_pCurrentForm!=nullptr){
        delete m_pCurrentForm;
        m_pCurrentForm=nullptr;
    }
}

void MainWindow::on_listViewSelector_clicked(const QModelIndex &index)
{
    qDebug()<<"row:"<<index.row();
    QString strTemp;
    strTemp = index.data().toString();

    QMessageBox msg;
    msg.setText(strTemp);
    msg.exec();
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
