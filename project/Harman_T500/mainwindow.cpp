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

#ifdef DB_SQLite
    createSQLiteConnection();
#endif

#ifdef DB_MSSQL
    //MS SQL Server 2008
    createMSSQLConnection();
#endif

//    NIVisaGPIB visaGPIB;
//    visaGPIB.sample_getCurrent();

    ViStatus status;
    status = m_niVisaGPIB.initGPIB();
    if(status == VI_SUCCESS){
        qDebug("initGPIB() OK");
    }
    else{
        qDebug("initGPIB() Fail");
    }

    m_pCurrentForm=new CurrentForm(this);
    ui->stackedWidget->addWidget(m_pCurrentForm);
    ui->stackedWidget->setCurrentIndex(0);
    m_pVoltageForm=new VoltageForm(this);
    ui->stackedWidget->addWidget(m_pVoltageForm);

    SetCurrDateTime();

    m_timer.start(1000,  this);

    QStringListModel* slm = new QStringListModel(this);
    QStringList* sl = new QStringList();
    sl->append("Current:DC");
//    sl->append("Voltage:DC");
    slm->setStringList(*sl);
    ui->listViewSelector->setModel(slm);
    delete sl;

    QModelIndex index = slm->index(Selector_Current);
    ui->listViewSelector->setCurrentIndex(index);
}

MainWindow::~MainWindow()
{
    delete ui;

    //    调用QSqlDatabase::removeDatabase()前需要先清除掉数据库对象，不然会有警告
    if(m_bSQLLiteConnection){
        if(m_dbSQLite.isValid()){
            m_dbSQLite.close();
            QSqlDatabase::removeDatabase("user");
            m_bSQLLiteConnection=false;
        }
    }
    if(m_bMSSQLConnection){
        if(m_dbMSSQL.isValid()){
            m_dbMSSQL.close();
            QSqlDatabase::removeDatabase("Lotus");
            m_bMSSQLConnection=false;
        }
    }

    if(m_pCurrentForm!=nullptr){
        delete m_pCurrentForm;
        m_pCurrentForm=nullptr;
    }
}

MainWindow *MainWindow::getMainWindow()
{
    foreach (QWidget *w, qApp->topLevelWidgets())
        if (MainWindow* mainWin = qobject_cast<MainWindow*>(w))
            return mainWin;
    return nullptr;
}

void MainWindow::on_listViewSelector_clicked(const QModelIndex &index)
{
    qDebug()<<"row:"<<index.row();

//    QString strTemp;
//    strTemp = index.data().toString();

//    QMessageBox msg;
//    msg.setText(strTemp);
//    msg.exec();

    ui->stackedWidget->setCurrentIndex(index.row());
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

bool MainWindow::createSQLiteConnection()
{
    m_bSQLLiteConnection=false;

    //    m_dbSQLite=QSqlDatabase::contains("qt_sql_default_connection")?QSqlDatabase::database("qt_sql_default_connection"):QSqlDatabase::addDatabase("QSQLITE");

//    if(QSqlDatabase::contains("qt_sql_default_connection"))
//        m_dbSQLite = QSqlDatabase::database("qt_sql_default_connection");
//    else
//        m_dbSQLite = QSqlDatabase::addDatabase("QSQLITE","user");

    m_dbSQLite = QSqlDatabase::addDatabase("QSQLITE","user");

    m_dbSQLite.setDatabaseName("mydb.db");

    //    QString name="root";
    //    QString password="123456";
    //    m_db.setUserName(name);
    //    m_db.setPassword(password);
    //    bool bOpen=m_db.open(name,password);
    //    qDebug()<<"bOpen:"<<bOpen;

    if(m_dbSQLite.open())
    {
        //"SN VARCHAR(50) UNIQUE,"

        //    select strftime('%Y/%m/%d %H:%M','now','localtime');
        //    2019/11/23 11:17
        //    select datetime('now');
        //    2019-11-23 03:13:55

        //    if(!sql_query.exec()) {
        //    qDebug() << sql_query.lastError();
        //    return false;
        //    }

        m_querySQLite=QSqlQuery(m_dbSQLite);
        bool bCreateTable=m_querySQLite.exec(
                    "CREATE TABLE  IF NOT EXISTS currentrecord("
                    "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "time TEXT,"
                    "sn VARCHAR(50),"
                    "idlecurrent VARCHAR(30),"
                    "idlecurrentpf  VARCHAR(10),"
                    "workcurrent VARCHAR(30),"
                    "workcurrentpf  VARCHAR(10),"
                    "chargecurrent  VARCHAR(30),"
                    "chargecurrentpf  VARCHAR(10),"
                    "idlemincurrent VARCHAR(30),"
                    "idlemaxcurrent  VARCHAR(30),"
                    "workmincurrent VARCHAR(30),"
                    "workmaxcurrent  VARCHAR(30),"
                    "chargemincurrent  VARCHAR(30),"
                    "chargemaxcurrent  VARCHAR(30),"
                    "pf VARCHAR(10))"
                    );
        if(!bCreateTable){
            QSqlError errorText=m_querySQLite.lastError();
            qDebug() << errorText;
            QMessageBox::warning(this,"warning",errorText.text());
        }
    }
    else
    {
        m_dbSQLite.close();

        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                              QObject::tr("Unable to establish a database connection.\n"
                                          "This example needs SQLite support. Please read "
                                          "the Qt SQL driver documentation for information how "
                                          "to build it.\n\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    m_bSQLLiteConnection=true;
    return true;
}

bool MainWindow::createMSSQLConnection()
{
    m_bMSSQLConnection=false;

    m_dbMSSQL=QSqlDatabase::addDatabase("QODBC","Lotus");
    qDebug()<<m_dbMSSQL.isValid();//检测驱动是否可用
    if(!m_dbMSSQL.isValid()){
        QMessageBox::warning(this,"warning","driver not loaded.");
        return false;
    }

    m_dbMSSQL.setDatabaseName(QString("DRIVER={SQL SERVER};"
                               "SERVER=%1;" //服务器名称
                               "DATABASE=%2;"//数据库名
                               "UID=%3;"           //登录名
                               "PWD=%4;"        //密码
                               )
                       .arg("192.168.0.246")
                       .arg("BaiduCodeTest")
                       .arg("sa")
                       .arg("Aa111111")
                       );
    if (!m_dbMSSQL.open())
    {
        m_dbSQLite.close();

        qDebug()<<"connect sql server failed!";

        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                              QObject::tr("Unable to establish a database connection.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
    else
    {
        m_bMSSQLConnection=true;
        qDebug()<<"connect sql server successfully!";

        m_queryMSSQL=QSqlQuery(m_dbMSSQL);
    }

    m_bMSSQLConnection=true;

    return true;
}

int MainWindow::getSupportDatabase()
{
    bool bSupportSQLite=false;
    bool bSupportMSSQL=false;
#if defined(DB_SQLite)
//    qDebug()<<"DB_SQLite";
    bSupportSQLite=true;
#endif

#if defined(DB_MSSQL)
//    qDebug()<<"DB_MSSQL";
    bSupportMSSQL=true;
#endif
    if(bSupportSQLite && bSupportMSSQL){
        m_databaseEnum=enum_SQLite_MSSQL;
    }
    else if(bSupportSQLite && !bSupportMSSQL){
        m_databaseEnum=enum_SQLite;
    }
    else if(!bSupportSQLite && bSupportMSSQL){
        m_databaseEnum=enum_MSSQL;
    }
    return  m_databaseEnum;
}

