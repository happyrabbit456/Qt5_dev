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


#include <QTableView>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>

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

    void initializeModel(QSqlQueryModel *model);
    void updateTableView();

public:
    bool initComboGPIB();
    void updateIdleCurrent(QString qstr);
    void updateWorkCurrent(QString qstr);
    void updateChargeCurrent(QString qstr);

    void ReadAppSettings();
    void WriteAppSettings();

    bool createSQLiteConnection();
    bool createMSSQLConnection();


//    bool bCreateTable=m_querySQLite.exec(
//                "CREATE TABLE  IF NOT EXISTS currentrecord("
//                "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
//                "time TEXT,"
//                "sn VARCHAR(50),"
//                "idlecurrent VARCHAR(30),"
//                "idlecurrentpf  VARCHAR(10),"
//                "workcurrent VARCHAR(30),"
//                "workcurrentpf  VARCHAR(10),"
//                "chargecurrent  VARCHAR(30),"
//                "chargecurrentpf  VARCHAR(10),"

//                "pf VARCHAR(10))"
//                );

public:
    NIVisaGPIB m_niVisaGPIB;

    QString m_sn;
    double m_idlecurrent;
    double m_idlecurrentpf;
    double m_workcurrent;
    double m_workcurrentpf;
    double m_chargecurrent;
    double m_chargecurrentpf;
    double m_pf;

private slots:
    void on_comboGPIBSelector_currentIndexChanged(int index);

    void on_btnReset_clicked();

    void on_btnTest_clicked();

    void on_btnLock_clicked();

    void on_btnUnlock_clicked();

private:
    Ui::CurrentForm *ui;

    QWizard wizard;
    QSettings *m_settings;

    QSqlQueryModel  *m_model;
};

#endif // CURRENTFORM_H
