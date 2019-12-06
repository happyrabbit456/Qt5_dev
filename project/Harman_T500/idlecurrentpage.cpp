#include "idlecurrentpage.h"

#include "currentform.h"

IdleCurrentPage::IdleCurrentPage(QWidget *parent)
{
    currentForm=qobject_cast<CurrentForm*>(parent);

    setTitle("Introduction");

    QLabel *label = new QLabel(tr("test idle current ......"));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);

//    registerField("sn*", snLineEdit);

}

bool IdleCurrentPage::validatePage()
{
    CurrentForm* pCurrentForm=static_cast<CurrentForm*>(currentForm);
    double d=0.000;
    pCurrentForm->m_niVisaGPIB.getCurrent(d);
    qDebug()<<d;

//    asprintf
    QString qstr=QString().sprintf("%5.3f",qAbs(d*1000));
    qDebug()<<"qstr:"<<qstr;

    pCurrentForm->updateIdleCurrent(qstr);

    return true;
}
