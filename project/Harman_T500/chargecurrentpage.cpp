#include "chargecurrentpage.h"

#include "currentform.h"

ChargeCurrentPage::ChargeCurrentPage(QWidget *parent)
{
    currentForm=qobject_cast<CurrentForm*>(parent);

    setTitle("Introduction");

    QLabel *label = new QLabel(tr("test charge current ......"));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);

//    registerField("sn*", snLineEdit);

}

bool ChargeCurrentPage::validatePage()
{
    CurrentForm* pCurrentForm=static_cast<CurrentForm*>(currentForm);
    double d=0.000;
    pCurrentForm->m_niVisaGPIB.getCurrent(d);
    qDebug()<<d;

//    asprintf
    QString qstr=QString().sprintf("%5.3f",qAbs(d*1000));
    qDebug()<<"qstr:"<<qstr;

    pCurrentForm->updateChargeCurrent(qstr);

    return true;
}
