#include "testform.h"
#include "ui_testform.h"

#include "mainwindow.h"

TestForm::TestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);

    m_mapString.insert(1,tr("Please set the parameters, then click Test button, the test can begin to go. "));

    resetTestHandle();
    clearMessagebox();
    appendMessagebox(m_mapString[1]);
}

TestForm::~TestForm()
{    
    delete ui;
}

bool TestForm::updateIdleCurrent(bool bOK, string str)
{
    if(bOK){
        double d=atof(str.c_str());
        d=qAbs(d*1000*1000); //uA
        QString qstr=QString().sprintf("%5.3f",qAbs(d));
        ui->editIdleCurrent->setText(qstr);

        m_idlecurrent=qstr;
        if(d<m_dMinIdleCurrent || d>m_dMaxIdleCurrent){
            m_idlecurrentpf="F";
            ui->labelIdleCurrentStatus->setVisible(true);
            ui->labelIdleCurrentStatus->setStyleSheet("color: rgb(255, 192, 128);background:red");
            ui->labelIdleCurrentStatus->setText("Fail");

            QString strValue=QString("The idle current value is %1 uA , threshold exceeded, the test fail.").arg(qstr);
            appendMessagebox(strValue);
        }
        else{
            m_idlecurrentpf="P";
            ui->labelIdleCurrentStatus->setVisible(true);
            ui->labelIdleCurrentStatus->setStyleSheet("color: rgb(255, 192, 128);background:green");
            ui->labelIdleCurrentStatus->setText("Pass");

            QString strValue=QString("The idle current value is %1 uA , the test pass.").arg(qstr);
            appendMessagebox(strValue);
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

            QString strValue=QString("The work current value is %1 mA , threshold exceeded, the test fail.").arg(qstr);
            appendMessagebox(strValue);
        }
        else{
            m_workcurrentpf="P";
            ui->labelWorkCurrentStatus->setVisible(true);
            ui->labelWorkCurrentStatus->setStyleSheet("color: rgb(255, 192, 128);background:green");
            ui->labelWorkCurrentStatus->setText("Pass");

            QString strValue=QString("The work current value is %1 mA , the test pass.").arg(qstr);
            appendMessagebox(strValue);
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

            QString strValue=QString("The charge current value is %1 mA , threshold exceeded, the test fail.").arg(qstr);
            appendMessagebox(strValue);
        }
        else{
            m_chargecurrentpf="P";
            ui->labelChargeCurrentStatus->setVisible(true);
            ui->labelChargeCurrentStatus->setStyleSheet("color: rgb(255, 192, 128);background:green");
            ui->labelChargeCurrentStatus->setText("Pass");

            QString strValue=QString("The charge current value is %1 mA , the test pass.").arg(qstr);
            appendMessagebox(strValue);
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
    if(bInsert){
        appendMessagebox("The test record is success to insert database.");
        QString str=QString().sprintf("The test record is success to save to local file. The dir path: %s .","D:\\database\\Harman_T500");
        appendMessagebox(str);
        emit updateDatabaseTabelView();
    }
    else{
        appendMessagebox("The test record is fail to insert database and save to local file. ");
    }

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

void TestForm::appendMessagebox(QString str)
{
    ui->editMessagebox->appendPlainText(str);
}

void TestForm::clearMessagebox()
{
    ui->editMessagebox->clear();
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

    clearMessagebox();
    appendMessagebox(m_mapString[1]);

#ifdef USE_WIZARD

    if(m_wizard!=nullptr){
        if(m_wizard->currentId()>-1){
            m_wizard->setVisible(false);
            m_wizard->close();
        }
    }

#endif
}

void TestForm::on_btnTest_clicked()
{
    resetTestHandle();

    MainWindow *pMainWindow=MainWindow::getMainWindow();
    if(pMainWindow->m_niVisaGPIB.m_mapGPIB.count()<=0){
        QMessageBox::warning(nullptr,"warning","Could not open a session to the VISA Resource Manager!\n");
        return;
    }

#ifdef USE_WIZARD
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
    QSize size=pMainWindow->size();
    pos.setX(pos.x()+size.width()+5);
    pos.setY(pos.y());
    m_wizard->move(pos);


    //禁用/隐藏/删除Qt对话框“标题栏”上的“?”帮助按钮这些按钮！
    Qt::WindowFlags flags = m_wizard->windowFlags();
    Qt::WindowFlags helpFlag =
            Qt::WindowContextHelpButtonHint;
    flags = flags & (~helpFlag);
    m_wizard->setWindowFlags(flags);

    m_wizard->setWindowTitle(QString::fromLocal8Bit("电流测试向导"));
    m_wizard->show();

#else
    m_snDlg=new SNDialog(this);
    //禁用/隐藏/删除Qt对话框“标题栏”上的“?”帮助按钮这些按钮！
    Qt::WindowFlags flags = m_snDlg->windowFlags();
    Qt::WindowFlags helpFlag =
            Qt::WindowContextHelpButtonHint;
    flags = flags & (~helpFlag);
    m_snDlg->setWindowFlags(flags);
    m_snDlg->setWindowTitle("Get scan code");
    m_snDlg->show();
#endif
}





