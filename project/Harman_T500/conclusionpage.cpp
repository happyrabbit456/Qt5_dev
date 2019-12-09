#include "conclusionpage.h"

#include "currentform.h"

ConclusionPage::ConclusionPage(QWidget *parent)
{
    currentForm=qobject_cast<CurrentForm*>(parent);

    setTitle(QString::fromLocal8Bit("电流测试结果"));

    CurrentForm* pCurrentForm=static_cast<CurrentForm*>(currentForm);
    QString idleDCStatus;
    QString workDCStatus;
    QString chargeDCStatus;
    pCurrentForm->getCurrentTestConclusion(idleDCStatus,workDCStatus,chargeDCStatus);

    QString idleResult;
    if(idleDCStatus.compare("P")==0){
        idleResult.append(QString::fromLocal8Bit("关机电流测试通过。"));
    }
    else{
        idleResult.append(QString::fromLocal8Bit("关机电流测试失败。"));
    }
    QString workResult;
    if(workDCStatus.compare("P")==0){
        workResult.append(QString::fromLocal8Bit("开机电流测试通过。"));
    }
    else{
        workResult.append(QString::fromLocal8Bit("开机电流测试失败。"));
    }
    QString chargeResult;
    if(chargeDCStatus.compare("P")==0){
        chargeResult.append(QString::fromLocal8Bit("充电电流测试通过。"));
    }
    else{
        chargeResult.append(QString::fromLocal8Bit("充电电流测试失败。"));
    }
    QString result;
    if(idleDCStatus.compare("P")==0
            && workDCStatus.compare("P")==0
            && chargeDCStatus.compare("P")==0){
        result.append(QString::fromLocal8Bit("电流测试通过。"));
    }
    else{
        result.append(QString::fromLocal8Bit("电流测试失败。"));
    }

    QLabel *labelIdle = new QLabel(idleResult);
    QLabel *labelWork = new QLabel(idleResult);
    QLabel *labelCharge = new QLabel(idleResult);
    QLabel *labelResult=new QLabel(result);
    labelIdle->setWordWrap(true);
    labelWork->setWordWrap(true);
    labelCharge->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(labelIdle);
    layout->setSpacing(20);
    layout->addWidget(labelWork);
    layout->setSpacing(20);
    layout->addWidget(labelCharge);
    layout->setSpacing(20);
    layout->addWidget(labelResult);
    setLayout(layout);
}

bool ConclusionPage::validatePage()
{
    CurrentForm* pCurrentForm=static_cast<CurrentForm*>(currentForm);
    bool bHandle = pCurrentForm->conclusionHandle();
    if(bHandle){
        return true;
    }
    else{
        return false;
    }
}
