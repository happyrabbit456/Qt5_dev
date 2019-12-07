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

    bool  updateSN(bool bOK,QString sn);
    bool updateIdleCurrent(bool bOK, string str);
    bool updateWorkCurrent(bool bOK, string str);
    bool updateChargeCurrent(bool bOK, string str);

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
    QString m_idlecurrent;
    QString m_idlecurrentpf;
    QString m_workcurrent;
    QString m_workcurrentpf;
    QString m_chargecurrent;
    QString m_chargecurrentpf;
    QString m_pf;

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
