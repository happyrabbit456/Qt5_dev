#include "testform.h"
#include "ui_testform.h"

#include "mainwindow.h"

#include <QStandardItemModel>
#include "showdatabaseform.h"

#include <QSqlQuery>

TestForm::TestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);

    if(parent!=nullptr){
        QSqlQuery query=((qobject_cast<MainWindow*>(parent)))->m_query;
        qDebug()<<"((qobject_cast<MainWindow*>(parent)))->m_query done.";
    }

    ui->lineEditSN->setText("");

    QImage image;
    image.load(":/res/images/None.jpg");
    ui->labelStatusImage->clear();
    ui->labelStatusImage->setPixmap(QPixmap::fromImage(image));
    ui->labelStatusImage->setScaledContents(true);
    ui->labelStatusImage->show();

    m_pPlainTextEditMsg=ui->plainTextEditMsg;
    m_pPlainTextEditMsg->clear();

    m_mapManufacturer.insert(TaiDe,"台德");
    m_mapManufacturer.insert(GuoGuang,"国光");

    ui->comboManufacturer->clear();
    QFont f;
    f.setBold(true);
    f.setPointSize(10);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::black);
    ui->comboManufacturer->setPalette(pa);
    ui->comboManufacturer->setFont(f);
    ui->comboManufacturer->addItem(m_mapManufacturer[TaiDe]);
    ui->comboManufacturer->addItem(m_mapManufacturer[GuoGuang]);

    QStandardItemModel *pItemModel = qobject_cast<QStandardItemModel*>(ui->comboManufacturer->model());
    for (int i = 0; i < ui->comboManufacturer->count(); i++) {
        pItemModel->item(i)->setForeground(QColor(0, 0, 255));
    }
    m_currManufacturerIndex=TaiDe;
    ui->comboManufacturer->setCurrentIndex(m_currManufacturerIndex);

    InitTestStatusMap();

    UpdateTestStatus(0,Status_Ready);

    m_settings = new QSettings("settings.ini", QSettings::IniFormat);
    ReadAppSettings();
}

TestForm::~TestForm()
{
    if(m_settings!=nullptr){
        delete m_settings;
        m_settings=nullptr;
    }
    delete ui;    
}

void TestForm::InitTestStatusMap()
{
    m_mapTestStatus.insert(1,"测试完成，测试结果Pass");
    m_mapTestStatus.insert(0,"测试准备中......");

    m_mapTestStatus.insert(-1,"测试失败，条码串不能为空串");
    m_mapTestStatus.insert(-2,"测试失败，条码串长度不为20");
    m_mapTestStatus.insert(-3,"测试失败，条码串中Baidu固定编码不是BD");
    m_mapTestStatus.insert(-4,"测试失败，条码串中组装厂字符和所选组装厂字符不匹配");
    m_mapTestStatus.insert(-5,"测试失败，条码串中喇叭单体颜色字符编码错误");
    m_mapTestStatus.insert(-6,"测试失败，条码串中物料字符编码错误");
    m_mapTestStatus.insert(-7,"测试失败，条码串中年份编码错误");
    m_mapTestStatus.insert(-8,"测试失败，条码串中月份编码错误");
    m_mapTestStatus.insert(-9,"测试失败，条码串中供应商编码错误");
    m_mapTestStatus.insert(-10,"测试失败，条码串中流水码编码错误");
    m_mapTestStatus.insert(-11,"测试失败，条码串重复，测试站已经有测试数据了");
}

void TestForm::ReadAppSettings()
{
    QString strWorkOrder=m_settings->value("WorkOrder","TJHS700315").toString();
    ui->lineEditWorkOrder->setText(strWorkOrder);

    QString strLine=m_settings->value("Line","A1").toString();
    ui->lineEditLine->setText(strLine);

    QString strModel=m_settings->value("Model","Baidu").toString();
    ui->lineEditModel->setText(strModel);

    QString strOPID=m_settings->value("OPID","065165").toString();
    ui->lineEditOPID->setText(strOPID);

    QString strTestStation=m_settings->value("TestStation","BarcodeCheck").toString();
    ui->lineEditTestStation->setText(strTestStation);

    QString strLineLeader=m_settings->value("LineLeader","065166").toString();
    ui->lineEditLineLeader->setText(strLineLeader);

    m_currManufacturerIndex=m_settings->value("ManufacturerIndex",TaiDe).toInt();
    ui->comboManufacturer->setCurrentIndex(m_currManufacturerIndex);
}

void TestForm::WriteAppSettings()
{
    QString strWorkOrder=ui->lineEditWorkOrder->text();
    m_settings->setValue("WorkOrder",strWorkOrder);

    QString strLine=ui->lineEditLine->text();
    m_settings->setValue("Line",strLine);

    QString strModel=ui->lineEditModel->text();
    m_settings->setValue("Model",strModel);

    QString strOPID=ui->lineEditOPID->text();
    m_settings->setValue("OPID",strOPID);

    QString strTestStation=ui->lineEditTestStation->text();
    m_settings->setValue("TestStation",strTestStation);

    QString strLineLeader=ui->lineEditLineLeader->text();
    m_settings->setValue("LineLeader",strLineLeader);

    m_settings->setValue("ManufacturerIndex",m_currManufacturerIndex);
}

bool TestForm::ScanningCodeHandle(QString strCode)
{
    //0:清空消息框
    m_pPlainTextEditMsg->clear();

    //1.开始检查条码
    m_pPlainTextEditMsg->appendPlainText(tr("开始检查Baidu speaker条码......"));

    //2.
    if(strCode.isNull() || strCode.isEmpty())
    {
        UpdateTestStatus(-1,Status_Fail);
        return false;
    }

    //3.
    if(strCode.length()!=20){
        UpdateTestStatus(-2,Status_Fail);
        return false;
    }

    //4.
    if(!strCode.startsWith("BD")){
        UpdateTestStatus(-3,Status_Fail);
        return false;
    }

    //5.
    bool bManufacturer=false;
    QString manufacturerCode=strCode.mid(2,4);//厂商
    switch (m_currManufacturerIndex) {
    case TaiDe:
        if(manufacturerCode.compare("0329")==0 ||manufacturerCode.compare("0330")==0)
        {
            bManufacturer=true;
        }
        else
        {
            bManufacturer=false;
        }
        break;
    case GuoGuang:
        bManufacturer = (manufacturerCode.compare("G001") == 0) ? true : false;
        break;
    }
    if(!bManufacturer){
        UpdateTestStatus(-4,Status_Fail);
        return false;
    }

    //6.
    if(!(strCode.at(6)==QChar('B') || strCode.at(6)==QChar('R'))){
        UpdateTestStatus(-5,Status_Fail);
    }

    //7.
    if(strCode.at(7)!=QChar('S')){
        UpdateTestStatus(-6,Status_Fail);
    }

    //8.
    QChar chYear = strCode.at(8);
    bool bYear=false;
    if(chYear == QChar('9')){
        bYear = true;
    }
    else if(chYear >= QChar('A') && chYear<=QChar('Z')){
        bYear = true;
    }
    else
    {
    }
    if(!bYear){
        UpdateTestStatus(-7,Status_Fail);
    }

    //9.
    QChar chMonth = strCode.at(9);
    bool bMonth=false;
    if(chMonth>='A'&&chMonth<='L')
    {
        bMonth=true;
    }
    if(!bMonth){
        UpdateTestStatus(-8,Status_Fail);
    }

    //10.
    QString supplierCode=strCode.mid(10,4); //供应商
    bool bSupplier=false;
    switch (m_currManufacturerIndex) {
    case TaiDe:
        if((manufacturerCode.compare("0329")==0 && supplierCode.compare("001A")==0) || (manufacturerCode.compare("0330")==0&&supplierCode.compare("001B")==0))
        {
            bSupplier=true;
        }
        break;
    case GuoGuang:
        if(supplierCode.compare("001A")==0 || supplierCode.compare("001B")==0)
        {
            bSupplier=true;
        }
        break;
    }
    if(!bSupplier){
        UpdateTestStatus(-9,Status_Fail);
        return false;
    }

    //11.
    QString flowCode=strCode.right(6);
    bool bFlowCode=true;

//    QByteArray ba = flowCode.toLatin1();//QString 转换为 char*
//    const char *temp = ba.data();
//    for (int i = 0; i < flowCode.length(); i++)
//    {
//        if (temp[i]<'0' || temp[i]>'9')
//        {
//            bFlowCode=false;
//            break;
//        }
//    }

    for (int i = 0; i < flowCode.length(); i++){
        if(!flowCode[i].isDigit()){
            bFlowCode=false;
            break;
        }
    }
    if(!bFlowCode){
        UpdateTestStatus(-10,Status_Fail);
        return false;
    }

    //12. 其他条件检测通过，插入数据库SN重复

    //OK.
    UpdateTestStatus(1,Status_Pass);


    return true;
}

bool TestForm::UpdateTestStatus(int errorCode, TestStatus status)
{
    //准备状态，不插入数据到数据库
    if(errorCode!=0)
    {
        //插入数据库
        MainWindow* pMainWindow=MainWindow::getMainWindow();
        if(pMainWindow!=nullptr){
            if(pMainWindow->m_bDBConnection){
                /**/
                QString strQuery;
//                strQuery="insert into record values(NULL,"
//                        "(select strftime('%Y/%m/%d %H:%M','now','localtime')),"
//                        "'TJHS700315',"
//                        "'Bardu',"
//                        "'BarcodeCheck',"
//                        "'A1',"
//                        "'065165',"
//                        "'065166',"
//                        "'BD0329BS9K001A195906',"
//                        "'台德',"
//                        "'P',"
//                        "0)";

                QString strTIME="(select strftime('%Y/%m/%d %H:%M','now','localtime'))";
                QString strWorkOrder=ui->lineEditWorkOrder->text();
                QString strLine=ui->lineEditLine->text();
                QString strModel=ui->lineEditModel->text();
                QString strOPID=ui->lineEditOPID->text();
                QString strTestStation=ui->lineEditTestStation->text();
                QString strLineLeader=ui->lineEditLineLeader->text();
                QString strSN=ui->lineEditSN->text();
                if(strSN.isNull() || strSN.isEmpty()){
                    strSN="";
                }
                QString strVendor=m_mapManufacturer[m_currManufacturerIndex];
                QString strPF;
                if(errorCode==1)
                    strPF="P";
                else
                    strPF="F";

                strQuery = QString("%1 %2 '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', %12)")
                        .arg("insert into record values(NULL,")
                        .arg("(select strftime('%Y/%m/%d %H:%M','now','localtime')),")
                        .arg(strWorkOrder)
                        .arg(strModel)
                        .arg(strTestStation)
                        .arg(strLine)
                        .arg(strOPID)
                        .arg(strLineLeader)
                        .arg(strSN)
                        .arg(strVendor)
                        .arg(strPF)
                        .arg(errorCode);


                qDebug()<<strQuery;

                bool bInsertRecord=pMainWindow->m_query.exec(strQuery);
                if(!bInsertRecord){
                    qDebug() << pMainWindow->m_query.lastError();
                }

            }
        }
    }


    m_pPlainTextEditMsg->appendPlainText(m_mapTestStatus[errorCode]);

    ui->lineEditErrorCode->setText(QString::number(errorCode,10));

    QLabel *label=ui->labelStatus;
    if(status==Status_Ready){
        //color: rgb(255, 192, 128);
        label->setStyleSheet("color: rgb(255, 192, 128)");
        label->setText("Ready");
        //None.jpg
        UpdateTestStatusImage(":/res/images/None.jpg");
    }
    else if(status==Status_Fail){
        //color: rgb(255, 0, 0);
        label->setStyleSheet("color: rgb(255, 192, 128)");
        label->setText("Fail");
        //Fail.jpg
        UpdateTestStatusImage(":/res/images/Fail.jpg");
    }
    else if(status==Status_Pass){
        //color: rgb(0, 128, 0);
        label->setStyleSheet("color: rgb(255, 192, 128)");
        label->setText("Pass");
        //Pass.jpg
        UpdateTestStatusImage(":/res/images/Pass.jpg");
    }
    else if(status==Status_Testing){
        //color: rgb(0, 0, 128);
        label->setStyleSheet("color: rgb(255, 192, 128)");
        label->setText("Testing");
        //Testing.jpg
        UpdateTestStatusImage(":/res/images/Testing.jpg");
    }

    QString info=m_mapTestStatus[errorCode];
    ui->labelResult->setText(info);

    return true;
}

void TestForm::UpdateTestStatusImage(QString imagePath)
{
    QLabel *label=ui->labelStatusImage;
    label->clear();
    label->setPixmap(QPixmap(imagePath));
    label->setScaledContents(true);
    label->show();
}

void TestForm::on_btnTest_clicked()
{
    //BD0329BS9K001A195906
    //BDG001BS9K001A093904
//    QString strCode="BD0329BS9K001A195906";
//    QString strCode="BDG001BS9K001A093904";
    QString strCode=ui->lineEditSN->text();

    ScanningCodeHandle(strCode);
}

void TestForm::on_comboManufacturer_currentIndexChanged(int index)
{
    m_currManufacturerIndex=index;
}

void TestForm::on_lineEditSN_textChanged(const QString &arg1)
{
//    qDebug()<<arg1;

    if(!arg1.isNull()&&!arg1.isEmpty()&&arg1.length()==1){
        m_currTime=QTime::currentTime();
        m_lastTime=m_currTime;

        m_strCurrChangedCode=arg1;
        m_strLastChangedCode=m_strCurrChangedCode;

        m_bAutoScan=true;
        m_checkAutoScannerTimer=new QTimer(this);
        connect(m_checkAutoScannerTimer, SIGNAL(timeout()), this, SLOT(CheckAutoScannerHandle()));
        m_checkAutoScannerTimer->start();
    }

    if(!arg1.isNull()&&!arg1.isEmpty()&&arg1.length()>1){
        m_currTime=QTime::currentTime();
        int elapsed = m_lastTime.msecsTo(m_currTime);

        m_lastTime=m_currTime;
        int pos=arg1.indexOf(m_strLastChangedCode);
        m_strLastChangedCode=arg1;

        if(elapsed<50 && pos==0){
            m_bAutoScan=true;
        }
        else{
            m_bAutoScan=false;
        }

        qDebug()<<"elapsed ="<<elapsed<<"ms"<<" pos:"<<pos<<" m_bAutoScan:"<<m_bAutoScan;
    }
}

void TestForm::CheckAutoScannerHandle()
{
    QTime checkTime=QTime::currentTime();
    int elapsed = m_lastTime.msecsTo(checkTime);

    if(!m_bAutoScan){
        if(m_checkAutoScannerTimer!=nullptr){
            m_checkAutoScannerTimer->stop();
            delete m_checkAutoScannerTimer;
            m_checkAutoScannerTimer=nullptr;
        }
    }

    if(elapsed>50 && m_bAutoScan) //扫描完成
    {
        qDebug()<<"m_strLastChangedCode:"<<m_strLastChangedCode;
        if(m_checkAutoScannerTimer!=nullptr){
            m_checkAutoScannerTimer->stop();
            delete m_checkAutoScannerTimer;
            m_checkAutoScannerTimer=nullptr;
        }

        ScanningCodeHandle(m_strLastChangedCode);
    }
}

void TestForm::on_btnLock_clicked()
{
    WriteAppSettings();

    ui->lineEditWorkOrder->setEnabled(false);
    ui->lineEditLine->setEnabled(false);
    ui->lineEditModel->setEnabled(false);
    ui->lineEditOPID->setEnabled(false);
    ui->lineEditTestStation->setEnabled(false);
    ui->lineEditLineLeader->setEnabled(false);
    ui->comboManufacturer->setEnabled(false);
}

void TestForm::on_btnUnlock_clicked()
{
    ui->lineEditWorkOrder->setEnabled(true);
    ui->lineEditLine->setEnabled(true);
    ui->lineEditModel->setEnabled(true);
    ui->lineEditOPID->setEnabled(true);
    ui->lineEditTestStation->setEnabled(true);
    ui->lineEditLineLeader->setEnabled(true);
    ui->comboManufacturer->setEnabled(true);
}
