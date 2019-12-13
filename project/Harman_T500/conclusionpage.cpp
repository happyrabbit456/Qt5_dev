#include "conclusionpage.h"

#include <QGridLayout>
#include <QVBoxLayout>

#include "testform.h"

#include "currentform.h"

ConclusionPage::ConclusionPage(QWidget *parent)
{
    currentForm=qobject_cast<TestForm*>(parent);

//    setTitle(QString::fromLocal8Bit("电流测试结果"));

    QFont font;
    font.setPointSize(12);

    TestForm* pCurrentForm=static_cast<TestForm*>(currentForm);
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

    labelIdle = new QLabel(idleResult);
    labelIdle->setFont(font);
    labelWork = new QLabel(idleResult);
    labelWork->setFont(font);
    labelCharge = new QLabel(idleResult);
    labelCharge->setFont(font);
    labelResult=new QLabel(result);
    labelResult->setFont(font);
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
    TestForm* pCurrentForm=static_cast<TestForm*>(currentForm);
    bool bHandle = pCurrentForm->conclusionHandle();
    if(bHandle){
        return true;
    }
    else{
        return false;
    }
}

void ConclusionPage::initializePage()
{
    TestForm* pCurrentForm=static_cast<TestForm*>(currentForm);
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

    labelIdle->setText(idleResult);
    labelWork->setText(workResult);
    labelCharge->setText(chargeResult);
    labelResult->setText(result);
}
