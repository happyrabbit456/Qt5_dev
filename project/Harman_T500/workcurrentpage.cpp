#include "workcurrentpage.h"

#include <QGridLayout>
#include <QVBoxLayout>

#include "testform.h"

#include "currentform.h"
#include "mainwindow.h"

WorkCurrentPage::WorkCurrentPage(QWidget *parent)
{
    currentForm=qobject_cast<TestForm*>(parent);

//    setTitle(QString::fromLocal8Bit("开机电流测试"));

    QFont font;
    font.setPointSize(12);

    QLabel *label = new QLabel(QString::fromLocal8Bit("请准备好开机电流可测状态，点击测试按钮，开始测试开机电流。"));
    label->setWordWrap(true);
    label->setFont(font);

    setButtonText(QWizard::NextButton,QString::fromLocal8Bit("测试"));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

bool WorkCurrentPage::validatePage()
{
    TestForm* pCurrentForm=static_cast<TestForm*>(currentForm);
    MainWindow *pMainWindow=MainWindow::getMainWindow();

    string value;
    pMainWindow->m_niVisaGPIB.reset();
//    pMainWindow->m_niVisaGPIB.autoZero(true);
    bool bGetCurrent=pMainWindow->m_niVisaGPIB.getCurrent(value);
    if(bGetCurrent){
        bool bUpdate=pCurrentForm->updateWorkCurrent(true,value);
        if(bUpdate){
            return true;
        }
    }

    return false;
}

