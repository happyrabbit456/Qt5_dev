﻿#include "testform.h"
#include "ui_testform.h"

#include "mainwindow.h"

TestForm::TestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);

    resetTestHandle();

    //    QXlsx::Document xlsx;
    //    xlsx.write("A1", "Hello Qt!");
    //    xlsx.saveAs("Test.xlsx");

    m_model = new QSqlQueryModel(ui->tableView);
    updateTableView();

    ui->tableView->scrollToBottom();
}

TestForm::~TestForm()
{
    if(m_model!=nullptr){
        delete m_model;
        m_model=nullptr;
    }

    delete ui;
}

bool TestForm::updateIdleCurrent(bool bOK, string str)
{
    if(bOK){
        double d=atof(str.c_str());
        d=qAbs(d*1000); //mA
        QString qstr=QString().sprintf("%5.3f",qAbs(d));
        ui->editIdleCurrent->setText(qstr);

        m_idlecurrent=qstr;
        if(d<m_dMinIdleCurrent || d>m_dMaxIdleCurrent){
            m_idlecurrentpf="F";
            ui->labelIdleCurrentStatus->setVisible(true);
            ui->labelIdleCurrentStatus->setStyleSheet("color: rgb(255, 192, 128);background:red");
            ui->labelIdleCurrentStatus->setText("Fail");
        }
        else{
            m_idlecurrentpf="P";
            ui->labelIdleCurrentStatus->setVisible(true);
            ui->labelIdleCurrentStatus->setStyleSheet("color: rgb(255, 192, 128);background:green");
            ui->labelIdleCurrentStatus->setText("Pass");
        }

        return true;
    }

    return false;
}

bool TestForm::updateWorkCurrent(bool bOK, string str)
{
    if(bOK){
        double d=atof(str.c_str());
        d=qAbs(d*1000); //mA
        QString qstr=QString().sprintf("%5.3f",qAbs(d));
        ui->editWorkCurrent->setText(qstr);

        m_workcurrent=qstr;
        if(d<m_dMinWorkCurrent || d>m_dMaxWorkCurrent){
            m_workcurrentpf="F";
            ui->labelWorkCurrentStatus->setVisible(true);
            ui->labelWorkCurrentStatus->setStyleSheet("color: rgb(255, 192, 128);background:red");
            ui->labelWorkCurrentStatus->setText("Fail");
        }
        else{
            m_workcurrentpf="P";
            ui->labelWorkCurrentStatus->setVisible(true);
            ui->labelWorkCurrentStatus->setStyleSheet("color: rgb(255, 192, 128);background:green");
            ui->labelWorkCurrentStatus->setText("Pass");
        }

        return true;
    }

    return false;
}

bool TestForm::updateChargeCurrent(bool bOK, string str)
{
    if(bOK){
        double d=atof(str.c_str());
        d=qAbs(d*1000); //mA
        QString qstr=QString().sprintf("%5.3f",qAbs(d));
        ui->editChargeCurrent->setText(qstr);

        m_chargecurrent=qstr;
        if(d<m_dMinChargeCurrent || d>m_dMaxChargeCurrent){
            m_chargecurrentpf="F";
            ui->labelChargeCurrentStatus->setVisible(true);
            ui->labelChargeCurrentStatus->setStyleSheet("color: rgb(255, 192, 128);background:red");
            ui->labelChargeCurrentStatus->setText("Fail");
        }
        else{
            m_chargecurrentpf="P";
            ui->labelChargeCurrentStatus->setVisible(true);
            ui->labelChargeCurrentStatus->setStyleSheet("color: rgb(255, 192, 128);background:green");
            ui->labelChargeCurrentStatus->setText("Pass");
        }

        return true;
    }

    return false;
}

bool TestForm::insertRecordHandle()
{
    QString strQuery;
    bool ret=false;

    MainWindow* pMainWindow=MainWindow::getMainWindow();
    int nSupportDatabase =pMainWindow->getSupportDatabase();
    if(pMainWindow!=nullptr && (nSupportDatabase==enum_SQLite||nSupportDatabase==enum_SQLite_MSSQL)){
        if(pMainWindow->m_bSQLLiteConnection){
            QString strTIME="(select strftime('%Y/%m/%d %H:%M','now','localtime'))";

            strQuery = QString("%1 %2 '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', '%14', '%15', '%16')")
                    .arg("insert into currentrecord values(NULL,")
                    .arg("(select strftime('%Y/%m/%d %H:%M','now','localtime')),")
                    .arg(m_sn)
                    .arg(m_idlecurrent)
                    .arg(m_idlecurrentpf)
                    .arg(m_workcurrent)
                    .arg(m_workcurrentpf)
                    .arg(m_chargecurrent)
                    .arg(m_chargecurrentpf)
                    .arg(QString().sprintf("%5.3f",m_dMinIdleCurrent))
                    .arg(QString().sprintf("%5.3f",m_dMaxIdleCurrent))
                    .arg(QString().sprintf("%5.3f",m_dMinWorkCurrent))
                    .arg(QString().sprintf("%5.3f",m_dMaxWorkCurrent))
                    .arg(QString().sprintf("%5.3f",m_dMinChargeCurrent))
                    .arg(QString().sprintf("%5.3f",m_dMaxChargeCurrent))
                    .arg(m_pf);

            qDebug()<<strQuery;

            bool bInsertRecord=pMainWindow->m_querySQLite.exec(strQuery);
            if(!bInsertRecord){
                qDebug() << pMainWindow->m_querySQLite.lastError();
                QMessageBox::warning(this,"warning",pMainWindow->m_querySQLite.lastError().text());
            }
            else{
                return true;
            }
        }
    }
    if(pMainWindow!=nullptr && (nSupportDatabase==enum_MSSQL||nSupportDatabase==enum_SQLite_MSSQL)){
        if(pMainWindow->m_bMSSQLConnection){
            QString strTIME="(select CONVERT(varchar(100) , getdate(), 111 )+' '+ Datename(hour,GetDate())+ ':'+Datename(minute,GetDate()))";

        }
    }

    return ret;
}

bool TestForm::conclusionHandle()
{
    if(m_idlecurrentpf.compare("P")==0
            &&m_workcurrentpf.compare("P")==0
            &&m_chargecurrentpf.compare("P")==0){
        m_pf="P";
        ui->labelResultStatus->setVisible(true);
        ui->labelResultStatus->setStyleSheet("color: rgb(255, 192, 128);background:green");
        ui->labelResultStatus->setText("Pass");
    }
    else{
        m_pf="F";
        ui->labelResultStatus->setVisible(true);
        ui->labelResultStatus->setStyleSheet("color: rgb(255, 192, 128);background:red");
        ui->labelResultStatus->setText("Fail");
    }

//    ui->tableView->setUpdatesEnabled(false);//暂停界面刷新
    bool bInsert=insertRecordHandle();

    updateTableView();

    ui->tableView->scrollToBottom();
    ui->tableView->update();

    return bInsert;
}

bool TestForm::getCurrentTestConclusion(QString &idleDCStatus, QString &workDCStatus, QString &chargeDCStatus)
{
    idleDCStatus=m_idlecurrentpf;
    workDCStatus=m_workcurrentpf;
    chargeDCStatus=m_chargecurrentpf;

    return true;
}

void TestForm::resetTestHandle()
{
    ui->labelIdleCurrentStatus->setVisible(false);
    ui->labelWorkCurrentStatus->setVisible(false);
    ui->labelChargeCurrentStatus->setVisible(false);
    ui->editIdleCurrent->setText("0.000");
    ui->editWorkCurrent->setText("0.000");
    ui->editChargeCurrent->setText("0.000");
    ui->labelResultStatus->setVisible(false);
}

void TestForm::on_btnReset_clicked()
{
    resetTestHandle();
}

void TestForm::on_btnTest_clicked()
{
    resetTestHandle();

    MainWindow *pMainWindow=MainWindow::getMainWindow();
    if(pMainWindow->m_niVisaGPIB.m_mapGPIB.count()<=0){
        QMessageBox::warning(nullptr,"warning","Could not open a session to the VISA Resource Manager!\n");
        return;
    }

    m_wizard=new QWizard(this);
    m_wizard->addPage(new SNPage(this));
    m_wizard->addPage(new IdleCurrentPage(this));
    m_wizard->addPage(new WorkCurrentPage(this));
    m_wizard->addPage(new ChargeCurrentPage(this));
    m_wizard->addPage(new ConclusionPage(this));

//    //去掉帮助按钮
//    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    //设置导航样式
//    m_wizard->setWizardStyle( QWizard::ModernStyle );

    //去掉向导页面按钮
//    m_wizard->setOption( QWizard::NoBackButtonOnStartPage );
//    m_wizard->setOption( QWizard::NoBackButtonOnLastPage );
//    m_wizard->setOption( QWizard::NoCancelButton );



    m_wizard->setWindowTitle(QString::fromLocal8Bit("电流测试向导"));
    m_wizard->show();

//    wizard.addPage(new SNPage(this));
//    wizard.addPage(new IdleCurrentPage(this));
//    wizard.addPage(new WorkCurrentPage(this));
//    wizard.addPage(new ChargeCurrentPage(this));
//    wizard.addPage(new ConclusionPage(this));

//    wizard.setWindowTitle(QString::fromLocal8Bit("电流测试向导"));
//    wizard.show();
}

void TestForm::initializeModel(QSqlQueryModel *model)
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

void TestForm::updateTableView()
{
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
     tableView->setColumnWidth(2, 120);
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
}

void TestForm::on_btnQuery_clicked()
{
    updateTableView();
}

void TestForm::on_btnExport_clicked()
{
    QXlsx::Document z_xlsx;
    QStringList z_titleList;
    QString z_filePathName;
    QString z_defaultFileName = QString::fromLocal8Bit("电流测试.xls");//tr("电流测试.xls");

    qDebug()<<z_defaultFileName;

    // 设置保存的默认文件名称 文件名_当前时间.xls
    QFileInfo z_fileinfo(z_defaultFileName);
    QDateTime z_curDateTime = QDateTime::currentDateTime();
    QString z_strCurTime = z_curDateTime.toString(tr("yyyyMMddhhmmss"));
    z_defaultFileName = z_fileinfo.baseName() + "_" + z_strCurTime + tr(".xls");

    // 获取保存文件路径
    QFileDialog *z_fileDlg = new QFileDialog(this);
    z_fileDlg->setWindowTitle(QString::fromLocal8Bit("保存文件"));
    z_fileDlg->setAcceptMode(QFileDialog::AcceptSave);
    z_fileDlg->selectFile(z_defaultFileName);
    z_fileDlg->setNameFilter(tr("Excel Files(*.xls *.xlsx)"));
    z_fileDlg->setDefaultSuffix(tr("xls"));

    if (z_fileDlg->exec() == QDialog::Accepted)
    {
        z_filePathName = z_fileDlg->selectedFiles().at(0);
    }

    // 保存文件添加后缀名
    z_fileinfo =  QFileInfo(z_filePathName);
    if (z_fileinfo.suffix() != "xls" && z_fileinfo.suffix() != tr("xlsx"))
    {
        z_filePathName += tr(".xls");
    }

    QXlsx::Format format1;/*设置该单元的样式*/
    format1.setFontColor(QColor(Qt::blue));/*文字为红色*/
    //           format1.setPatternBackgroundColor(QColor(152,251,152));/*北京颜色*/
    format1.setFontSize(15);/*设置字体大小*/
    format1.setHorizontalAlignment(QXlsx::Format::AlignHCenter);/*横向居中*/
    //           format1.setBorderStyle(QXlsx::Format::BorderDashDotDot);/*边框样式*/

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
            z_xlsx.setColumnWidth(i, 20);
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
    z_xlsx.saveAs(z_filePathName);
}
