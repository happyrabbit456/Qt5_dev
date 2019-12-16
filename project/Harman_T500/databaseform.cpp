#include "databaseform.h"
#include "ui_databaseform.h"

#include "mainwindow.h"

DatabaseForm::DatabaseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseForm)
{
    ui->setupUi(this);

    m_model = new QSqlQueryModel(ui->tableView);
    updateTableView();

    ui->tableView->scrollToBottom();
}

DatabaseForm::~DatabaseForm()
{
    if(m_model!=nullptr){
        delete m_model;
        m_model=nullptr;
    }

    delete ui;
}


void DatabaseForm::initializeModel(QSqlQueryModel *model)
{
    //数据库数据
    MainWindow* pMainWindow=MainWindow::getMainWindow();
    if(pMainWindow!=nullptr){
        /*
        if(pMainWindow->m_bDBConnection){
            model->setQuery("select * from currentrecord",pMainWindow->m_db);
            if (model->lastError().isValid()){
                qDebug() << model->lastError();
                QMessageBox::warning(this,"warning",model->lastError().text());
            }
        }
        */
        int nSupportDatabase =pMainWindow->getSupportDatabase();
        if(nSupportDatabase==enum_SQLite){
            if(pMainWindow->m_bSQLLiteConnection){
                model->setQuery("select * from currentrecord",pMainWindow->m_dbSQLite);
                if (model->lastError().isValid()){
                    qDebug() << model->lastError();
                    QMessageBox::warning(this,"warning",model->lastError().text());
                }
            }
        }
        else{
            if(pMainWindow->m_bMSSQLConnection){
                model->setQuery("select * from currentrecord",pMainWindow->m_dbMSSQL);
                if (model->lastError().isValid()){
                    qDebug() << model->lastError();
                    QMessageBox::warning(this,"warning",model->lastError().text());
                }
            }
        }
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("time"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("sn"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("idlecurrent"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("idlecurrentpf"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("workcurrent"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("workcurrentpf"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("chargecurrent"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("chargecurrentpf"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("idlemincurrent"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("idlemaxcurrent"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("workmincurrent"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("workmaxcurrent"));
    model->setHeaderData(13, Qt::Horizontal, QObject::tr("chargemincurrent"));
    model->setHeaderData(14, Qt::Horizontal, QObject::tr("chargemaxcurrent"));
    model->setHeaderData(15, Qt::Horizontal, QObject::tr("pf"));
}

void DatabaseForm::updateTableView()
{
    qDebug()<<"DatabaseForm::updateTableView() enter.";
    QTableView *tableView=ui->tableView;
    initializeModel(m_model);
    ui->tableView->setModel(m_model);

    //只读
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置选中模式为选中行
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置选中单行
    tableView->setSelectionMode( QAbstractItemView::SingleSelection);

    tableView->setSortingEnabled(false);
    tableView->verticalHeader()->hide();
    tableView->setWordWrap(false);

    tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);//表头居中
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);//设置固定宽度

    // column width
    tableView->setColumnWidth(0, 100);
    tableView->setColumnWidth(1, 120);
    tableView->setColumnWidth(2, 180);
    tableView->setColumnWidth(3, 100);
    tableView->setColumnWidth(4, 100);
    tableView->setColumnWidth(5, 100);
    tableView->setColumnWidth(6, 100);
    tableView->setColumnWidth(7, 100);
    tableView->setColumnWidth(8, 120);
    tableView->setColumnWidth(9, 120);
    tableView->setColumnWidth(10, 120);
    tableView->setColumnWidth(11, 120);
    tableView->setColumnWidth(12, 120);
    tableView->setColumnWidth(13, 120);
    tableView->setColumnWidth(14, 120);
    tableView->setColumnWidth(15, 120);

    /*设置tableview等宽*/
    //    QHeaderView* headerView = ui->tableWidget->horizontalHeader();
    //    headerView->setSectionResizeMode(QHeaderView::Stretch);
    /*或者下面的代码*/
    //    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //    ui->tableView->resizeColumnsToContents();

    ui->tableView->show();

    ui->tableView->scrollToBottom();
    ui->tableView->update();
}

void DatabaseForm::on_btnQuery_clicked()
{
    updateTableView();
}

void DatabaseForm::on_btnExport_clicked()
{
    QXlsx::Document z_xlsx;
    QStringList z_titleList;
    QString z_filePathName;

    QString z_defaultFileName = QString::fromLocal8Bit("电流测试.xlsx");//tr("电流测试.xls");

    qDebug()<<z_defaultFileName;

    // 设置保存的默认文件名称 文件名_当前时间.xls
    QFileInfo z_fileinfo(z_defaultFileName);
    QDateTime z_curDateTime = QDateTime::currentDateTime();
    QString z_strCurTime = z_curDateTime.toString(tr("yyyyMMddhhmmss"));
    z_defaultFileName = z_fileinfo.baseName() + "_" + z_strCurTime + tr(".xlsx");

    // 获取保存文件路径
    QFileDialog *z_fileDlg = new QFileDialog(this);
    z_fileDlg->setWindowTitle(QString::fromLocal8Bit("保存文件"));
    z_fileDlg->setAcceptMode(QFileDialog::AcceptSave);
    z_fileDlg->selectFile(z_defaultFileName);
    z_fileDlg->setNameFilter(tr("Excel Files(*.xlsx)"));
    z_fileDlg->setDefaultSuffix(tr("xlsx"));

    if (z_fileDlg->exec() == QDialog::Accepted)
    {
        z_filePathName = z_fileDlg->selectedFiles().at(0);
    }

    // 保存文件添加后缀名
    z_fileinfo =  QFileInfo(z_filePathName);
    if (z_fileinfo.suffix() != tr("xlsx"))
    {
        z_filePathName += tr(".xlsx");
    }

    QXlsx::Format format1;/*设置该单元的样式*/
    format1.setFontColor(QColor(Qt::blue));/*文字为红色*/
    //           format1.setPatternBackgroundColor(QColor(152,251,152));/*北京颜色*/
    format1.setFontSize(15);/*设置字体大小*/
    format1.setHorizontalAlignment(QXlsx::Format::AlignHCenter);/*横向居中*/
    format1.setBorderStyle(QXlsx::Format::BorderThin);//QXlsx::Format::BorderDashDotDot);/*边框样式*/

    // 设置excel任务标题
    z_titleList << "id" << "time" << "sn" << "idlecurrent"<<"idlecurrentpf"
                <<"workcurrent"<<"workcurrentpf"<<"chargecurrent"<< "chargecurrentpf"
               << "idlemincurrent"<<"idlemaxcurrent"<<"workmincurrent"<<"workmaxcurrent"
               <<"chargemincurrent"<<"chargemaxcurrent"<<"pf";
    for (int i = 0; i < z_titleList.size(); i++)
    {
        //           z_xlsx.write(1, i+1, z_titleList.at(i));

        z_xlsx.write(1, i+1, z_titleList.at(i),format1);
    }

    // 设置烈宽
    for(int i=1;i<17;i++){
        if(i==2 || i==3){
            z_xlsx.setColumnWidth(i, 30);
        }
        else{
            z_xlsx.setColumnWidth(i, 30);
        }
    }

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

    // 保存文件
    bool bSaveAs=z_xlsx.saveAs(z_filePathName);
    if(bSaveAs){
        if (QMessageBox::question(nullptr,QString::fromLocal8Bit("完成"),QString::fromLocal8Bit("文件已经导出，是否现在打开？"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(z_filePathName))); //乱码
        }
    }
    else{
        QMessageBox::warning(nullptr,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("保存到Excel文件失败"));
    }
}
