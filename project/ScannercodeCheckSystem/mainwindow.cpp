#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);






#ifdef DB_SQLite
    m_bDBConnection=createSQLiteConnection();


    //"SN VARCHAR(50) UNIQUE,"

    //    select strftime('%Y/%m/%d %H:%M','now','localtime');
    //    2019/11/23 11:17
    //    select datetime('now');
    //    2019-11-23 03:13:55

    //    if(!sql_query.exec()) {
    //    qDebug() << sql_query.lastError();
    //    return false;
    //    }

    if(m_bDBConnection){
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
            QSqlError errorText=m_query.lastError();
            qDebug() << errorText;
            QMessageBox::warning(this,"warning",errorText.text());
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
#else
    //mssqlservice2008
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
    if(m_bDBConnection){
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

bool MainWindow::createMSSQLConnection()
{
    m_db=QSqlDatabase::addDatabase("QODBC");
    qDebug()<<m_db.isValid();//检测驱动是否可用
    if(!m_db.isValid()){
        QMessageBox::warning(this,"warning","driver not loaded.");
        return false;
    }

    m_db.setDatabaseName(QString("DRIVER={SQL SERVER};"
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
    if (!m_db.open())
    {
        m_bDBConnection=false;
        qDebug()<<"connect sql server failed!";

        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                              QObject::tr("Unable to establish a database connection.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
    else
    {
        m_bDBConnection=true;
        qDebug()<<"connect sql server successfully!";

        m_query=QSqlQuery(m_db);

        return true;
    }

    /*
     * 判断表存在
    if object_id(N'record',N'U') is not null
    print '存在'
    else
    print '不存在'

    IF EXISTS  (SELECT  * FROM dbo.SysObjects WHERE ID = object_id(N'[record]') AND OBJECTPROPERTY(ID, 'IsTable') = 1)
    PRINT '存在'
    else
    PRINT'不存在'
    */

    /*
        CREATE TABLE record(
            ID	INTEGER PRIMARY KEY,
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


    一.
    SQL数据库中，建立表时没有将id列标识规范设置为“是”。所以大家在创建表的时候一定将id设为自动增加id，标识之类的。

    二.
    我们尝试去修改字段值时，sql server 会提示 您对无法重新创建的表进行了更改或者启用了“阻止保存要求重新创建表的更改”选项
    可以做以下修改：
    打开 SQL SERVER连接工具

    工具 ——》选项——》设计器（designer）
    1
    去掉勾选 “阻止保存要求重新创建表的更改”
    ————————————————
    版权声明：本文为CSDN博主「Wei_Yw」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
    原文链接：https://blog.csdn.net/Wei_Yw/article/details/88992236

    insert into dbo.record values(
       (select CONVERT(varchar(100) , getdate(), 111 )+' '+ Datename(hour,GetDate())+ ':'+Datename(minute,GetDate())),
       'TJHS700315',
       'Bardu',
       'BarcodeCheck',
       'A1',
       '065165',
       '065166',
       'BD0329BS9K001A195906',
       '台德',
       'P',
       0);
    */
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

