#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QStandardItemModel>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#if defined(DB_SQLite)

    qDebug()<<"DB_SQLite";
#endif

#if defined(DB_MSSQL)

    qDebug()<<"DB_MSSQL";
#endif

    //mssqlservice2008
    QSqlDatabase msdb=QSqlDatabase::addDatabase("QODBC");
    qDebug()<<msdb.isValid();//检测驱动是否可用
    msdb.setDatabaseName(QString("DRIVER={SQL SERVER};"
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
    if (!msdb.open())
    {
        qDebug()<<"connect sql server failed!";

    }
    else
    {
        qDebug()<<"connect sql server successfully!";
    }



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
//    ————————————————
//            版权声明：本文为CSDN博主「xjcwzp」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
//            原文链接：https://blog.csdn.net/xjcwzp/article/details/96836314

}

MainWindow::~MainWindow()
{
    delete ui;


    qDebug()<<"deconstructor done.";
}

void MainWindow::on_pushButton_clicked()
{
//    QMessageBox::information(this, tr("No database driver selected"),
//                             tr("Please select a database driver"));

//    QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
//        QObject::tr("Unable to establish a database connection.\n"
//                    "This example needs SQLite support. Please read "
//                    "the Qt SQL driver documentation for information how "
//                    "to build it.\n\n"
//                    "Click Cancel to exit."), QMessageBox::Cancel);


//    int ret = QMessageBox::warning(this, tr("My Application"),
//                                    tr("The document has been modified.\n"
//                                       "Do you want to save your changes?"),
//                                    QMessageBox::Save | QMessageBox::Discard
//                                    | QMessageBox::Cancel,
//                                    QMessageBox::Save);


//    QMessageBox msgBox;
//    msgBox.setText("The document has been modified.");
//    msgBox.exec();


//    QMessageBox msgBox;
//    msgBox.setText("The document has been modified.");
//    msgBox.setInformativeText("Do you want to save your changes?");
//    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//    msgBox.setDefaultButton(QMessageBox::Save);
//    int ret = msgBox.exec();
//    switch (ret) {
//       case QMessageBox::Save:
//           // Save was clicked
//           break;
//       case QMessageBox::Discard:
//           // Don't Save was clicked
//           break;
//       case QMessageBox::Cancel:
//           // Cancel was clicked
//           break;
//       default:
//           // should never be reached
//           break;
//     }



//    QMessageBox msgBox;
//    QPushButton *connectButton = msgBox.addButton(tr("Connect"), QMessageBox::ActionRole);
//    QPushButton *abortButton = msgBox.addButton(QMessageBox::Abort);

//    msgBox.exec();

//    if (msgBox.clickedButton() == connectButton) {
//        // connect
//    } else if (msgBox.clickedButton() == abortButton) {
//        // abort
//    }


    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("Delete Album"),
                                   tr("Are you sure you want to "
                                      "delete '%1' by '%2'?")
                                   .arg("title", "artist"),
                                   QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::Yes) {

    }


//    QMessageBox::about(this, tr("About"), tr("The SQL Browser demonstration "
//        "shows how a data browser can be used to visualize the results of SQL"
//                                             "statements on a live database"));


}
