#include "workcurrentpage.h"

#include "currentform.h"

WorkCurrentPage::WorkCurrentPage(QWidget *parent)
{
    currentForm=qobject_cast<CurrentForm*>(parent);

    setTitle("Introduction");

    QLabel *label = new QLabel(tr("test work current ......"));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);

//    registerField("sn*", snLineEdit);

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

