#include "chargecurrentpage.h"

#include <QGridLayout>
#include <QVBoxLayout>

#include "testform.h"

#include "currentform.h"
#include "mainwindow.h"

ChargeCurrentPage::ChargeCurrentPage(QWidget *parent)
{
    currentForm=qobject_cast<TestForm*>(parent);

//    setTitle(QString::fromLocal8Bit("充电电流测试"));

    QFont font;
    font.setPointSize(11);

    QLabel *label = new QLabel(QString::fromLocal8Bit("开机电流测试操作完成了，现在请连接USB线，准备好充电电流测试，然后点击测试按钮，开始测试。"));
    label->setWordWrap(true);
    label->setFont(font);

    setButtonText(QWizard::NextButton,QString::fromLocal8Bit("测试"));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

bool ChargeCurrentPage::validatePage()
{
    TestForm* pCurrentForm=static_cast<TestForm*>(currentForm);
    MainWindow *pMainWindow=MainWindow::getMainWindow();

    string value;
    pMainWindow->m_niVisaGPIB.reset();
//    pMainWindow->m_niVisaGPIB.autoZero(true);
    bool bGetCurrent=pMainWindow->m_niVisaGPIB.getCurrent(value);
    if(bGetCurrent){
        bool bUpdate=pCurrentForm->updateChargeCurrent(true,value);
        if(bUpdate){
            return true;
        }
    }

    return false;
}
