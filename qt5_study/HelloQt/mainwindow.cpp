#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QStandardItemModel>

#include <QMessageBox>

#include <QFileInfo>
#include <QFileDialog>
#include <QTextCodec>

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





}

MainWindow::~MainWindow()
{
    delete ui;


    qDebug()<<"deconstructor done.";
}

void MainWindow::toExcel()
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
//    ————————————————
//            版权声明：本文为CSDN博主「xjcwzp」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
//            原文链接：https://blog.csdn.net/xjcwzp/article/details/96836314


    QXlsx::Document z_xlsx;
       QStringList z_titleList;
       QString z_filePathName;
       QString z_defaultFileName = "刻录任务汇总.xls";

       // 设置保存的默认文件名称 文件名_当前时间.xls
       QFileInfo z_fileinfo(z_defaultFileName);
       QDateTime z_curDateTime = QDateTime::currentDateTime();
       QString z_strCurTime = z_curDateTime.toString("yyyyMMddhhmmss");
       z_defaultFileName = z_fileinfo.baseName() + "_" + z_strCurTime + ".xls";

       // 获取保存文件路径
       QFileDialog *z_fileDlg = new QFileDialog(this);
       z_fileDlg->setWindowTitle("保存文件");
       z_fileDlg->setAcceptMode(QFileDialog::AcceptSave);
       z_fileDlg->selectFile(z_defaultFileName);
       z_fileDlg->setNameFilter("Excel Files(*.xls *.xlsx)");
       z_fileDlg->setDefaultSuffix("xls");

       if (z_fileDlg->exec() == QDialog::Accepted)
       {
           z_filePathName = z_fileDlg->selectedFiles().at(0);
       }

       // 保存文件添加后缀名
       z_fileinfo =  QFileInfo(z_filePathName);
       if (z_fileinfo.suffix() != "xls" && z_fileinfo.suffix() != "xlsx")
       {
           z_filePathName += ".xls";
       }

       QXlsx::Format format1;/*设置该单元的样式*/
           format1.setFontColor(QColor(Qt::blue));/*文字为红色*/
//           format1.setPatternBackgroundColor(QColor(152,251,152));/*北京颜色*/
           format1.setFontSize(15);/*设置字体大小*/
           format1.setHorizontalAlignment(QXlsx::Format::AlignHCenter);/*横向居中*/
//           format1.setBorderStyle(QXlsx::Format::BorderDashDotDot);/*边框样式*/

       // 设置excel任务标题
       z_titleList << "test0" << "test1" << "test2" << "test3";
       for (int i = 0; i < z_titleList.size(); i++)
       {
//           z_xlsx.write(1, i+1, z_titleList.at(i));

           z_xlsx.write(1, i+1, z_titleList.at(i),format1);
       }

       // 设置烈宽
       z_xlsx.setColumnWidth(1, 10);
       z_xlsx.setColumnWidth(2, 10);
       z_xlsx.setColumnWidth(3, 10);
       z_xlsx.setColumnWidth(4, 15);

       int i,j;

       //QTableView 获取列数
       int colcount=ui->tableView->model()->columnCount();// tableView->model->columnCount();
       //QTableView 获取行数
       int rowcount=ui->tableView->model()->rowCount();// tableView->model->rowCount();

       //数据区 QTableView 获取表格数据部分
       for(i=0;i<rowcount;i++) //行数
       {
           for (j=0;j<colcount;j++)   //列数
           {
               QModelIndex index = ui->tableView->model()->index(i, j);
               QString strdata=ui->tableView->model()->data(index).toString();
               z_xlsx.write(i+2,j+1,strdata);
           }
       }


//       // 获取表格内容设置excel
//       int z_row = modelBurnTask->rowCount();
//       int z_col = modelBurnTask->columnCount() - 1;// 最后一列为图标，不保存
//       for (int i = 0; i < z_row; i++)
//       {
//           for (int j = 0; j < z_col; j++)
//           {
//               z_xlsx.write(i+2, j+1 ,modelBurnTask->index(i, j).data().toString());
//           }
//       }

       // 保存文件
       z_xlsx.saveAs(z_filePathName);
}

void MainWindow::on_pushButton_clicked()
{

    toExcel();

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


//    QMessageBox::StandardButton button;
//    button = QMessageBox::question(this, tr("Delete Album"),
//                                   tr("Are you sure you want to "
//                                      "delete '%1' by '%2'?")
//                                   .arg("title", "artist"),
//                                   QMessageBox::Yes | QMessageBox::No);

//    if (button == QMessageBox::Yes) {

//    }


//    QMessageBox::about(this, tr("About"), tr("The SQL Browser demonstration "
//        "shows how a data browser can be used to visualize the results of SQL"
//                                             "statements on a live database"));


}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    qDebug()<<arg1;
}

void MainWindow::on_pushButton_2_clicked()
{
//    QString path=QString().fromLocal8Bit("D:\\database\\20191211170204.xls");
//    QXlsx::Document xlsx(path);

    QString path=QString().sprintf("%s","D:\\database\\刻录任务汇总_20191211170204 - 副本.xls");
    QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题
    std::string name = code->fromUnicode(path).data();
    QString path2=QString(QString::fromLocal8Bit(name.c_str()));
    QXlsx::Document xlsx(path2);


    QXlsx::Workbook *workBook = xlsx.workbook();
    QXlsx::Worksheet *workSheet = static_cast<QXlsx::Worksheet*>(workBook->sheet(0));

    qDebug()<<"rowCount:"<<workSheet->dimension().rowCount();
    qDebug()<<"columnCount:"<<workSheet->dimension().columnCount();
    int rowCount=workSheet->dimension().rowCount();
    int columnCount=workSheet->dimension().columnCount();

    int i=rowCount;
    for(int j=1;j<=columnCount;j++){
        xlsx.write(i + 1, j, QString("ddd"));
    }

    xlsx.save();
}
