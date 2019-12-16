#include "idlecurrentpage.h"

#include <QGridLayout>
#include <QVBoxLayout>

#include "testform.h"

#include "currentform.h"
#include "mainwindow.h"

IdleCurrentPage::IdleCurrentPage(QWidget *parent)
{
    currentForm=qobject_cast<TestForm*>(parent);

//    setTitle(QString::fromLocal8Bit("关机电流测试"));

    QFont font;
    font.setPointSize(11);

    QLabel *label = new QLabel(QString::fromLocal8Bit("二维码扫描操作完成了，现在请准备好关机电流测试，然后点击测试按钮，开始测试。"));
    label->setWordWrap(true);
    label->setFont(font);

    setButtonText(QWizard::NextButton,QString::fromLocal8Bit("测试"));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

bool IdleCurrentPage::validatePage()
{
    TestForm* pCurrentForm=static_cast<TestForm*>(currentForm);
    MainWindow *pMainWindow=MainWindow::getMainWindow();
    string value;
    pCurrentForm->appendMessagebox(tr("The idle current test begin to test ......"));
    pMainWindow->m_niVisaGPIB.reset();
//    pMainWindow->m_niVisaGPIB.autoZero(true);
    bool bGetCurrent=pMainWindow->m_niVisaGPIB.getCurrent(value);
    if(bGetCurrent){
        bool bUpdate=pCurrentForm->updateIdleCurrent(true,value);
        if(bUpdate){
            return true;
        }
    }

    return false;
}
