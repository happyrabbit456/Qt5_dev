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
    font.setPointSize(12);

    QLabel *label = new QLabel(QString::fromLocal8Bit("请准备好充电电流可测状态，点击测试按钮，开始测试充电电流。"));
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
    bool bGetCurrent=pMainWindow->m_niVisaGPIB.getCurrent(value);
    if(bGetCurrent){
        bool bUpdate=pCurrentForm->updateChargeCurrent(true,value);
        if(bUpdate){
            return true;
        }
    }

    return false;
}
