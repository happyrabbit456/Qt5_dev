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
