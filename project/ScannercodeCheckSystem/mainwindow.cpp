#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#ifdef DB_SQLite
    createSQLiteConnection();
#endif

#ifdef DB_MSSQL
    //MS SQL Server 2008
    createMSSQLConnection();
#endif

    //Logo图片显示
//    ui->labelLogo->clear();
//    ui->labelLogo->setPixmap(QPixmap(":/res/images/MINAMI_logo.jpg"));
//    ui->labelLogo->setScaledContents(true);
//    ui->labelLogo->show();


    m_pTestForm=new TestForm(this);
    m_pShowDataForm=new ShowDataBaseForm(this);
    m_pVersionForm=new VersionForm(this);

    ui->tabWidget->insertTab(0,m_pTestForm,tr("Test"));
    ui->tabWidget->insertTab(1,m_pShowDataForm,tr("ShowDatabase"));
    ui->tabWidget->insertTab(2,m_pVersionForm,"ReviseHistory");

    ui->lineEditDuration->setText("00:00:00");
    SetCurrDateTime();

    m_timer.start(1000,  this);
}

MainWindow::~MainWindow()
{
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

    m_timer.stop();

    delete m_pTestForm;
    m_pTestForm=nullptr;
    delete m_pShowDataForm;
    m_pShowDataForm=nullptr;
    delete m_pVersionForm;
    m_pVersionForm=nullptr;

    delete ui;
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
                    "CREATE TABLE  IF NOT EXISTS record("
                    "ID	INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "TIME TEXT,"
                    "WorkOrder	VARCHAR(30),"
                    "Model VARCHAR(30),"
                    "TestStation  VARCHAR(30),"
                    "Line VARCHAR(20),"
                    "OPID VARCHAR(20),"
                    "LineLeader VARCHAR(20),"
                    "SN VARCHAR(50),"
                    "Vendor VARCHAR(30),"
                    "PF VARCHAR(10),"
                    "ErrorCode INTEGER)"
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

MainWindow *MainWindow::getMainWindow()
{
    foreach (QWidget *w, qApp->topLevelWidgets())
        if (MainWindow* mainWin = qobject_cast<MainWindow*>(w))
            return mainWin;
    return nullptr;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int r=QMessageBox::question(this,tr("Last Hint"),tr("Are you sure you want to quit?"),QMessageBox::Yes|QMessageBox::Default,QMessageBox::No|QMessageBox::Escape);
    if (r==QMessageBox::Yes){
        if(m_pTestForm!=nullptr){
            m_pTestForm->WriteAppSettings();
        }
        if(m_bSQLLiteConnection){
            if(m_dbSQLite.isValid()){
                {
                    m_dbSQLite.close();
                }
                QSqlDatabase::removeDatabase("user");
                m_bSQLLiteConnection=false;
            }

        }
        if(m_bMSSQLConnection){
            if(m_dbMSSQL.isValid()){
                {
                    m_dbMSSQL.close();
                }
                QSqlDatabase::removeDatabase("Lotus");
                m_bMSSQLConnection=false;
            }
        }
        event->accept();
    }
    else
        event->ignore();
}

