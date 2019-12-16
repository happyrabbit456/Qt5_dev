#include "snpage.h"

#include <QGridLayout>
#include <QVBoxLayout>

#include <QAbstractButton>

#include "testform.h"

SNPage::SNPage(QWidget *parent)
{
    currentForm=qobject_cast<TestForm*>(parent);

//    setTitle(QString::fromLocal8Bit("获取扫描码"));

    QFont font;
    font.setPointSize(11);

    QLabel *label = new QLabel(QString::fromLocal8Bit("扫描枪准备完成，请扫描测试模块上的二维码到编辑框内，成功后向导会自动跳转。"));
    label->setWordWrap(true);
    label->setFont(font);

    QLabel *nameLabel = new QLabel("SN");
    nameLabel->setFont(font);
    snLineEdit = new QLineEdit;
    snLineEdit->setFont(font);

    snLineEdit->setObjectName("snLineEdit");

    connect(snLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(snLineEdit_textChanged(const QString &)));

    QGridLayout *layout_SN = new QGridLayout;
    layout_SN->addWidget(nameLabel, 0, 0);
    layout_SN->addWidget(snLineEdit, 0, 1);

    snLineEdit->installEventFilter(this);


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
//    layout->addStretch();
    layout->addSpacing(20);
    layout->addLayout(layout_SN);
    setLayout(layout);

    registerField("sn*", snLineEdit);

    resetSNPage();
}

bool SNPage::validatePage()
{
    qDebug()<<"validatePage() done.";

    TestForm* pCurrentForm=static_cast<TestForm*>(currentForm);
    pCurrentForm->m_sn=snLineEdit->text();

    resetSNPage();

    return true;
}

void SNPage::resetSNPage()
{
    snLineEdit->setFocusPolicy(Qt::StrongFocus);
    snLineEdit->setFocus();
    snLineEdit->setText("");

    m_currTime=QTime::currentTime();
    m_lastTime=m_currTime;

    m_strCurrChangedCode=snLineEdit->text();//arg1;
    m_strLastChangedCode=m_strCurrChangedCode;

    m_bAutoScan=false;
}

void SNPage::snLineEdit_textChanged(const QString &arg1)
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

void SNPage::resetAutoScannerTimer()
{
    QMutexLocker locker(&m_mutexCheckTimer);
    if(m_checkAutoScannerTimer.isActive()){
        disconnect(&m_checkAutoScannerTimer, SIGNAL(timeout()), this, SLOT(CheckAutoScannerHandle()));
        m_checkAutoScannerTimer.stop();
    }
}

void SNPage::CheckAutoScannerHandle()
{
    QTime checkTime=QTime::currentTime();
    int elapsed = m_lastTime.msecsTo(checkTime);

    qDebug()<<"CheckAutoScannerHandle()"<<" elapsed:"<<elapsed<<" "<<m_bAutoScan;

    if(elapsed>50 && m_bAutoScan) //扫描完成
    {
        qDebug()<<"m_strLastChangedCode:"<<m_strLastChangedCode;

        QString strCode=snLineEdit->text();
        ScanningCodeHandle(strCode);

        resetAutoScannerTimer();

        m_bAutoScan=false;
    }
}

bool SNPage::ScanningCodeHandle(QString strCode)
{
    TestForm* pCurrentForm=static_cast<TestForm*>(currentForm);
    pCurrentForm->m_sn=snLineEdit->text();

    QAbstractButton *bt = this->wizard()->button(QWizard::NextButton);
    bt->click();

    return true;
}

bool SNPage::eventFilter(QObject *obj, QEvent  *event)
{
    if(obj==snLineEdit){
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

            if(keyEvent->key() == Qt::Key_Return)//16777220)//enter
            {
                qDebug()<<snLineEdit->text();

                QString strLineEdit=snLineEdit->text();
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
