#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    m_bSQLiteConnection=createSQLiteConnection();


    //"SN VARCHAR(50) UNIQUE,"

    //    select strftime('%Y/%m/%d %H:%M','now','localtime');
    //    2019/11/23 11:17
    //    select datetime('now');
    //    2019-11-23 03:13:55

    //    if(!sql_query.exec()) {
    //    qDebug() << sql_query.lastError();
    //    return false;
    //    }

    if(m_bSQLiteConnection){
        m_query=QSqlQuery(m_db);
        bool bCreateTable=m_query.exec(
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
            qDebug() << m_query.lastError();
        }
    }

    /*
    CREATE TABLE  IF NOT EXISTS record(
        ID	INTEGER PRIMARY KEY AUTOINCREMENT,
        TIME TEXT,
        WorkOrder	VARCHAR(30),
        Model VARCHAR(30),
        TestStation  VARCHAR(30),
        Line VARCHAR(20),
        OPID VARCHAR(20),
        LineLeader VARCHAR(20),
        SN VARCHAR(50),
        Vendor VARCHAR(30),
        PF VARCHAR(10),
        ErrorCode INTEGER
    );

    insert into record values(NULL,
           (select strftime('%Y/%m/%d %H:%M','now','localtime')),
           'TJHS700315',
           'Bardu',
           'BarcodeCheck',
           'A1',
           '065165',
           '065166',
           'BD0329BS9K001A195906',
           '',
           'P',
           0);
    */




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
    if(m_bSQLiteConnection){
        m_db.close();
        QSqlDatabase::removeDatabase("user");
    }

    m_timer.stop();

    delete m_pTestForm;
    delete m_pShowDataForm;
    delete m_pVersionForm;

    delete ui;
}

bool MainWindow::createSQLiteConnection()
{
    //    m_db=QSqlDatabase::contains("qt_sql_default_connection")?QSqlDatabase::database("qt_sql_default_connection"):QSqlDatabase::addDatabase("QSQLITE");

    if(QSqlDatabase::contains("qt_sql_default_connection"))
        m_db = QSqlDatabase::database("qt_sql_default_connection");
    else
        m_db = QSqlDatabase::addDatabase("QSQLITE","user");

    m_db.setDatabaseName("mydb.db");

    //    QString name="root";
    //    QString password="123456";
    //    m_db.setUserName(name);
    //    m_db.setPassword(password);
    //    bool bOpen=m_db.open(name,password);
    //    qDebug()<<"bOpen:"<<bOpen;

    if (!m_db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                              QObject::tr("Unable to establish a database connection.\n"
                                          "This example needs SQLite support. Please read "
                                          "the Qt SQL driver documentation for information how "
                                          "to build it.\n\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    return true;
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

