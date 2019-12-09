#include "snpage.h"

#include "currentform.h"

SNPage::SNPage(QWidget *parent)
{
    currentForm=qobject_cast<CurrentForm*>(parent);

    setTitle(QString::fromLocal8Bit("获取扫描码"));

    QLabel *label = new QLabel(QString::fromLocal8Bit("请先扫描测试设备上的二维码，然后点击下一步。"));
    label->setWordWrap(true);

    QLabel *nameLabel = new QLabel("SN");
    snLineEdit = new QLineEdit;

    QGridLayout *layout_SN = new QGridLayout;
    layout_SN->addWidget(nameLabel, 0, 0);
    layout_SN->addWidget(snLineEdit, 0, 1);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
//    layout->addStretch();
    layout->addSpacing(20);
    layout->addLayout(layout_SN);
    setLayout(layout);

    registerField("sn*", snLineEdit);
}

bool SNPage::validatePage()
{
    qDebug()<<"validatePage() done.";

    CurrentForm* pCurrentForm=static_cast<CurrentForm*>(currentForm);

    bool bUpdate = pCurrentForm->updateSN(true, snLineEdit->text());
    if(bUpdate){
        return true;
    }
    else{
        return false;
    }
}
