#include "idlecurrentpage.h"

#include <QGridLayout>
#include <QVBoxLayout>

#include "testform.h"

#include "currentform.h"
#include "mainwindow.h"

IdleCurrentPage::IdleCurrentPage(QWidget *parent)
{
    currentForm=qobject_cast<TestForm*>(parent);

    setTitle(QString::fromLocal8Bit("关机电流测试"));

    QLabel *label = new QLabel(QString::fromLocal8Bit("请准备好关机电流可测状态，点击测试按钮，开始测试关机电流。"));
    label->setWordWrap(true);

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
    bool bGetCurrent=pMainWindow->m_niVisaGPIB.getCurrent(value);
    if(bGetCurrent){
        bool bUpdate=pCurrentForm->updateIdleCurrent(true,value);
        if(bUpdate){
            return true;
        }
    }

    return false;
}
