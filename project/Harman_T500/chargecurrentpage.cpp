#include "chargecurrentpage.h"

#include "currentform.h"

ChargeCurrentPage::ChargeCurrentPage(QWidget *parent)
{
    currentForm=qobject_cast<CurrentForm*>(parent);

    setTitle(QString::fromLocal8Bit("充电电流测试"));

    QLabel *label = new QLabel(QString::fromLocal8Bit("请准备好充电电流可测状态，点击测试按钮，开始测试充电电流。"));
    label->setWordWrap(true);

    setButtonText(QWizard::NextButton,QString::fromLocal8Bit("测试"));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

bool ChargeCurrentPage::validatePage()
{
    CurrentForm* pCurrentForm=static_cast<CurrentForm*>(currentForm);

    string value;
    bool bGetCurrent=pCurrentForm->m_niVisaGPIB.getCurrent(value);
    if(bGetCurrent){
        bool bUpdate=pCurrentForm->updateChargeCurrent(true,value);
        if(bUpdate){
            return true;
        }
    }

    return false;
}
