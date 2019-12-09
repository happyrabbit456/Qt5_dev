#include "workcurrentpage.h"

#include "currentform.h"

WorkCurrentPage::WorkCurrentPage(QWidget *parent)
{
    currentForm=qobject_cast<CurrentForm*>(parent);

    setTitle(QString::fromLocal8Bit("开机电流测试"));

    QLabel *label = new QLabel(QString::fromLocal8Bit("请准备好开机电流可测状态，点击测试按钮，开始测试开机电流。"));
    label->setWordWrap(true);

    setButtonText(QWizard::NextButton,QString::fromLocal8Bit("测试"));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

bool WorkCurrentPage::validatePage()
{
    CurrentForm* pCurrentForm=static_cast<CurrentForm*>(currentForm);

    string value;
    bool bGetCurrent=pCurrentForm->m_niVisaGPIB.getCurrent(value);
    if(bGetCurrent){
        bool bUpdate=pCurrentForm->updateWorkCurrent(true,value);
        if(bUpdate){
            return true;
        }
    }

    return false;
}

