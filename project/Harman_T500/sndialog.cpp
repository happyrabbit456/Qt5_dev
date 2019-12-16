#include "sndialog.h"
#include "ui_sndialog.h"

#include <QDebug>
#include <QMessageBox>

#include "testform.h"
#include "mainwindow.h"

SNDialog::SNDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SNDialog)
{
    ui->setupUi(this);

    resetSNPage();

    ui->editDlgSN->installEventFilter(this);
}

SNDialog::~SNDialog()
{
    delete ui;
}

void SNDialog::on_editDlgSN_textChanged(const QString &arg1)
{
    qDebug()<<arg1;

    /*
    1.判断是扫描枪扫描
    字符变动+1，并且和上次字符间隔时间小于50ms，考虑原有字符串中间插入的情况不能处理，所以比较字串的方法不可取
    2.判断扫描完成
    第一步成立，启动定时器判断扫描完成
    */


    m_currTime=QTime::currentTime();
    int elapsed = m_lastTime.msecsTo(m_currTime);

//    m_lastTime=m_currTFime;
//    int pos=arg1.indexOf(m_strLastChangedCode);
//    m_strLastChangedCode=arg1;

//    if(elapsed<50 && pos==0){
    if(elapsed<50){
        if(!m_bAutoScan){
            m_bAutoScan=true;

            {
                QMutexLocker locker(&m_mutexCheckTimer);
                connect(&m_checkAutoScannerTimer, SIGNAL(timeout()), this, SLOT(CheckAutoScannerHandle()));
                m_checkAutoScannerTimer.start(50);
            }
        }
    }
    else{
        m_bAutoScan=false;
    }
    m_lastTime=m_currTime;
}

void SNDialog::resetSNPage()
{
    QLineEdit *snEdit=ui->editDlgSN;
    snEdit->setFocusPolicy(Qt::StrongFocus);
    snEdit->setFocus();
    snEdit->setText("");

    m_currTime=QTime::currentTime();
    m_lastTime=m_currTime;

    m_strCurrChangedCode=snEdit->text();//arg1;
    m_strLastChangedCode=m_strCurrChangedCode;

    m_bAutoScan=false;
}

void SNDialog::resetAutoScannerTimer()
{
    QMutexLocker locker(&m_mutexCheckTimer);
    if(m_checkAutoScannerTimer.isActive()){
        disconnect(&m_checkAutoScannerTimer, SIGNAL(timeout()), this, SLOT(CheckAutoScannerHandle()));
        m_checkAutoScannerTimer.stop();
    }
}

void SNDialog::CheckAutoScannerHandle()
{
    QTime checkTime=QTime::currentTime();
    int elapsed = m_lastTime.msecsTo(checkTime);

//    qDebug()<<"CheckAutoScannerHandle()"<<" elapsed:"<<elapsed<<" "<<m_bAutoScan;

    if(elapsed>50 && m_bAutoScan) //扫描完成
    {
        qDebug()<<"m_strLastChangedCode:"<<m_strLastChangedCode;

        QString strCode=ui->editDlgSN->text();
        ScanningCodeHandle(strCode);

        resetAutoScannerTimer();

        m_bAutoScan=false;
    }
}

bool SNDialog::ScanningCodeHandle(QString strCode)
{
    Q_UNUSED(strCode)

    QLineEdit *snEdit=ui->editDlgSN;

    TestForm* pCurrentForm=qobject_cast<TestForm*>(this->parentWidget());

    pCurrentForm->m_sn=ui->editDlgSN->text();

    if(snEdit->text().isEmpty()){
        pCurrentForm->appendMessagebox(tr("Two-dimensional code cannot be empty, please try again."));

        QMessageBox::warning(nullptr, tr("warning"),
                                       tr("Two-dimensional code cannot be empty, please try again."),
                                       QMessageBox::Ok);
        return false;
    }
    else{
        QString code=QString("Two-dimensional code is %1 .").arg(snEdit->text());
        pCurrentForm->appendMessagebox(code);
    }

    resetSNPage();

    this->close();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Idel current test");
    msgBox.setText(QString::fromLocal8Bit("请准备好关机电流测试，然后点击测试按钮。"));
    msgBox.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("测试"));
    int ret=msgBox.exec();
    if(QMessageBox::Ok == ret)
    {
        MainWindow *pMainWindow=MainWindow::getMainWindow();
        string value;
        pCurrentForm->appendMessagebox(tr("The idle current test begin to test ......"));
        pMainWindow->m_niVisaGPIB.reset();
    //    pMainWindow->m_niVisaGPIB.autoZero(true);
        bool bGetCurrent=pMainWindow->m_niVisaGPIB.getCurrent(value);
        if(bGetCurrent){
            bool bUpdate=pCurrentForm->updateIdleCurrent(true,value);
            if(bUpdate){
            }

            msgBox.setWindowTitle("Work current test");
            msgBox.setText(QString::fromLocal8Bit("请准备好开机电流测试，然后点击测试按钮。"));
            msgBox.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("测试"));
            int ret=msgBox.exec();
            if(QMessageBox::Ok == ret)
            {
                string value;
                pMainWindow->m_niVisaGPIB.reset();
            //    pMainWindow->m_niVisaGPIB.autoZero(true);
                bool bGetCurrent=pMainWindow->m_niVisaGPIB.getCurrent(value);
                if(bGetCurrent){
                    bool bUpdate=pCurrentForm->updateWorkCurrent(true,value);
                    if(bUpdate){
                    }
                }


                msgBox.setWindowTitle("Charge current test");
                msgBox.setText(QString::fromLocal8Bit("请准备好充电电流测试，然后点击测试按钮。"));
                msgBox.setButtonText(QMessageBox::Ok,QString::fromLocal8Bit("测试"));
                int ret=msgBox.exec();
                if(QMessageBox::Ok == ret)
                {
                    string value;
                    pMainWindow->m_niVisaGPIB.reset();
                //    pMainWindow->m_niVisaGPIB.autoZero(true);
                    bool bGetCurrent=pMainWindow->m_niVisaGPIB.getCurrent(value);
                    if(bGetCurrent){
                        bool bUpdate=pCurrentForm->updateChargeCurrent(true,value);
                        if(bUpdate){
                        }

                        pCurrentForm->conclusionHandle();
                    }
                }
            }
        }
    }

    return true;
}

bool SNDialog::eventFilter(QObject *obj, QEvent  *event)
{
    if(obj==ui->editDlgSN){
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

            if(keyEvent->key() == Qt::Key_Return)//16777220)//enter
            {
                qDebug()<<ui->editDlgSN->text();

                QString strLineEdit=ui->editDlgSN->text();
                bool ret=ScanningCodeHandle(strLineEdit);
                if(ret)
                {
                    event->accept();
                    return true;
                }
            }
        }
    }

    // standard event processing
    return QObject::eventFilter(obj, event);
}

void SNDialog::closeEvent(QCloseEvent *event)
{
//    qDebug()<<"closeEvent(QCloseEvent *event) enter";

    Q_UNUSED(event)
}

