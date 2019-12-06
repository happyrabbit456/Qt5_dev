#ifndef CURRENTFORM_H
#define CURRENTFORM_H

#include <QWidget>
#include <QDebug>


#include <QtWidgets>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include "nivisagpib.h"

#include <QtXlsx>
#include "xlsxdocument.h"

#include "snpage.h"
#include "idlecurrentpage.h"
#include "workcurrentpage.h"
#include "chargecurrentpage.h"
#include "conclusionpage.h"

namespace Ui {
class CurrentForm;
}

class CurrentForm : public QWidget
{
    Q_OBJECT

public:
    explicit CurrentForm(QWidget *parent = nullptr);
    ~CurrentForm();

protected:
    void resetTestHandle();

public:
    bool initComboGPIB();
    void updateIdleCurrent(QString qstr);
    void updateWorkCurrent(QString qstr);
    void updateChargeCurrent(QString qstr);

public:
    NIVisaGPIB m_niVisaGPIB;

private slots:
    void on_comboGPIBSelector_currentIndexChanged(int index);

    void on_btnReset_clicked();

    void on_btnTest_clicked();

private:
    Ui::CurrentForm *ui;

    QWizard wizard;
};

#endif // CURRENTFORM_H
