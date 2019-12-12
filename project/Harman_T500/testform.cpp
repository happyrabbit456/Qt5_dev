#include "testform.h"
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

        //update result label
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
//            QString strTIME="(select strftime('%Y/%m/%d %H:%M','now','localtime'))";

            QDateTime z_curDateTime = QDateTime::currentDateTime();
            QString strTIME = z_curDateTime.toString(tr("yyyy/MM/dd hh:mm"));

//            strQuery = QString("%1 %2 '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', '%14', '%15', '%16')")
            strQuery = QString("%1 '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', '%14', '%15', '%16')")
                    .arg("insert into currentrecord values(NULL,")
//                    .arg("(select strftime('%Y/%m/%d %H:%M','now','localtime')),")
                    .arg(strTIME)
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
                //直接写到文件
                writeRecordToExcel(strTIME);

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

void TestForm::writeOnewRecord(QXlsx::Document &xlsx,int rowCount,int columnCount, QString strTIME,QVariant newIDValue)
{
    int i=rowCount;
    for(int j=1;j<=columnCount;j++){
        switch (j) {
        case 1:
            xlsx.write(i + 1, j,newIDValue);
            break;
        case 2:
            xlsx.write(i + 1, j,strTIME);
            break;
        case 3:
            xlsx.write(i + 1, j,m_sn);
            break;
        case 4:
            xlsx.write(i + 1, j,m_idlecurrent);
            break;
        case 5:
            xlsx.write(i + 1, j,m_idlecurrentpf);
            break;
        case 6:
            xlsx.write(i + 1, j,m_workcurrent);
            break;
        case 7:
            xlsx.write(i + 1, j,m_workcurrentpf);
            break;
        case 8:
            xlsx.write(i + 1, j,m_chargecurrent);
            break;
        case 9:
            xlsx.write(i + 1, j,m_chargecurrentpf);
            break;
        case 10:
            xlsx.write(i + 1, j,QString().sprintf("%5.3f",m_dMinIdleCurrent));
            break;
        case 11:
            xlsx.write(i + 1, j,QString().sprintf("%5.3f",m_dMaxIdleCurrent));
            break;
        case 12:
            xlsx.write(i + 1, j,QString().sprintf("%5.3f",m_dMinWorkCurrent));
            break;
        case 13:
            xlsx.write(i + 1, j,QString().sprintf("%5.3f",m_dMaxWorkCurrent));
            break;
        case 14:
            xlsx.write(i + 1, j,QString().sprintf("%5.3f",m_dMinChargeCurrent));
            break;
        case 15:
            xlsx.write(i + 1, j,QString().sprintf("%5.3f",m_dMaxChargeCurrent));
            break;
        case 16:
            xlsx.write(i + 1, j,m_pf);
            break;
        }
    }
}

void TestForm::writeRecordToExcel(QString strTIME)
{
    //直接写到文件
    QString strDatabaseDir=QString().sprintf("%s","D:\\database\\Harman_T500");

    QDateTime z_curDateTime = QDateTime::currentDateTime();
    QString z_strCurTime = z_curDateTime.toString(tr("yyyyMMdd"));
    QString fileName = strDatabaseDir+"\\"+QString("dc") + "_" + z_strCurTime + tr(".xlsx");
    qDebug()<<"fileName:"<<fileName;

    QDir dir(strDatabaseDir);
    if(!dir.exists()){
        bool ok = dir.mkpath(strDatabaseDir);//创建多级目录
        qDebug()<<"dir.mkpath(strDatabaseDir) ok:"<<ok;
    }

    qDebug()<<"dir.exists() true";
    QFile file(fileName);
    if(file.exists())
    {
        qDebug()<<"file.exists() true";
        //存在文件
        QXlsx::Document xlsx(fileName); //OK


        QXlsx::Workbook *workBook = xlsx.workbook();
        QXlsx::Worksheet *workSheet = static_cast<QXlsx::Worksheet*>(workBook->sheet(0));

        qDebug()<<"rowCount:"<<workSheet->dimension().rowCount();
        qDebug()<<"columnCount:"<<workSheet->dimension().columnCount();
        int rowCount=workSheet->dimension().rowCount();
        int columnCount=workSheet->dimension().columnCount();

        QVariant lastid= xlsx.read(rowCount,1);
        int newid=lastid.toInt()+1;
        QVariant newIDValue(newid);

        writeOnewRecord(xlsx,rowCount,columnCount, strTIME,newIDValue);

        xlsx.save();
    }
    else{
        //不存在文件
        QXlsx::Document z_xlsx;
        QStringList z_titleList;

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


        int rowCount=2;
        int columnCount=16;
        int newid=1;
        QVariant newIDValue(newid);

        writeOnewRecord(z_xlsx,rowCount,columnCount, strTIME,newIDValue);

        // 保存文件
        z_xlsx.saveAs(fileName);
    }
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

    //设置导航样式
    m_wizard->setWizardStyle( QWizard::ModernStyle );

    //去掉向导页面按钮
    m_wizard->setOption( QWizard::NoBackButtonOnStartPage );
    m_wizard->setOption( QWizard::NoBackButtonOnLastPage );
    m_wizard->setOption( QWizard::NoCancelButton );

    //去掉BackButton
    QList<QWizard::WizardButton> layout;
    layout << QWizard::Stretch // << QWizard::BackButton << QWizard::CancelButton
           << QWizard::NextButton << QWizard::FinishButton;
    m_wizard->setButtonLayout(layout);


    m_wizard->resize(320,160);
    QPoint pos=pMainWindow->pos();
    pos.setX(pos.x()-120);
    pos.setY(pos.y()+500);
    m_wizard->move(pos);


    //禁用/隐藏/删除Qt对话框“标题栏”上的“?”帮助按钮这些按钮！
    Qt::WindowFlags flags = m_wizard->windowFlags();
    Qt::WindowFlags helpFlag =
    Qt::WindowContextHelpButtonHint;
    flags = flags & (~helpFlag);
    m_wizard->setWindowFlags(flags);

    m_wizard->setWindowTitle(QString::fromLocal8Bit("电流测试向导"));
    m_wizard->show();
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

