#include "snpage.h"

#include "currentform.h"

SNPage::SNPage(QWidget *parent)
{
    currentForm=qobject_cast<CurrentForm*>(parent);

    setTitle("Introduction");

    QLabel *label = new QLabel(tr("scan code ......"));
    label->setWordWrap(true);

    QLabel *nameLabel = new QLabel("SN");
    QLineEdit *snLineEdit = new QLineEdit;

    QGridLayout *layout_SN = new QGridLayout;
    layout_SN->addWidget(nameLabel, 0, 0);
    layout_SN->addWidget(snLineEdit, 0, 1);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addLayout(layout_SN);
    setLayout(layout);

//    registerField("sn*", snLineEdit);

}

bool SNPage::validatePage()
{
//    qDebug()<<"validatePage() done.";

    CurrentForm* pCurrentForm=static_cast<CurrentForm*>(currentForm);

//    double d=0.000;
//    pCurrentForm->m_niVisaGPIB.getCurrent(d);
//    qDebug()<<d;

////    asprintf
//    QString qstr=QString().sprintf("%5.3f",qAbs(d*1000));
//    qDebug()<<"qstr:"<<qstr;

//    pCurrentForm->updateIdleCurrent(qstr);

    return true;
}
