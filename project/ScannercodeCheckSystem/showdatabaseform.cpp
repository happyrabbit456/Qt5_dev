#include "showdatabaseform.h"
#include "ui_showdatabaseform.h"

ShowDataBaseForm::ShowDataBaseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowDataBaseForm)
{
    ui->setupUi(this);

    //    TestTableView();

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
           '0');
    */
}

ShowDataBaseForm::~ShowDataBaseForm()
{
    //    调用QSqlDatabase::removeDatabase()前需要先清除掉数据库对象，不然会有警告
    if(m_bSQLiteConnection){
        m_db.close();
        QSqlDatabase::removeDatabase("user");
    }

    delete ui;
}

void ShowDataBaseForm::testTableView()
{
    QStandardItemModel *model = new QStandardItemModel(0,4);
    ui->tableView->setModel(model);

    //只读
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置选中模式为选中行
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置选中单行
    ui->tableView->setSelectionMode( QAbstractItemView::SingleSelection);


    //添加表头
    model->setHeaderData(0,Qt::Horizontal,"test0");
    model->setHeaderData(1,Qt::Horizontal,"test1");
    model->setHeaderData(2,Qt::Horizontal,"test2");
    model->setHeaderData(3,Qt::Horizontal,"test3");

    int row=0;
    //添加行
    for(;row<4;row++)
    {
        model->insertRows(row,1);

        model->setData(model->index(row,0), QString::number(row)+ "0");
        model->setData(model->index(row,1),QString::number(row)+ "1");
        model->setData(model->index(row,2),QString::number(row)+ "2");
        model->setData(model->index(row,3),QString::number(row)+ "3");

    }

    ui->tableView->show();
}

bool ShowDataBaseForm::createSQLiteConnection()
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

void ShowDataBaseForm::initializeModel(QSqlTableModel *model)
{
    model->setTable("record");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TIME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("WorkOrder"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Model"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TestStation"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Line"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("OPID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("LineLeader"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("SN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Vendor"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PF"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ErrorCode"));
}


