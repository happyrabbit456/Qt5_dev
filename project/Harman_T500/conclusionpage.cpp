#include "conclusionpage.h"

#include "currentform.h"

ConclusionPage::ConclusionPage(QWidget *parent)
{
    currentForm=qobject_cast<CurrentForm*>(parent);

    setTitle("Introduction");

    QLabel *label = new QLabel(tr("test conclusion ......"));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);

//    registerField("sn*", snLineEdit);

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
