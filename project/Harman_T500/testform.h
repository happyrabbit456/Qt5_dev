#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>

#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

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

#include <string>

using namespace std;

namespace Ui {
class TestForm;
}

class TestForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestForm(QWidget *parent = nullptr);
    ~TestForm();

protected:
    void initializeModel(QSqlQueryModel *model);
    void updateTableView();

protected:
    void resetTestHandle();

public:

    bool updateIdleCurrent(bool bOK, string str);
    bool updateWorkCurrent(bool bOK, string str);
    bool updateChargeCurrent(bool bOK, string str);

    bool insertRecordHandle();
    bool conclusionHandle();

    bool getCurrentTestConclusion(QString &idleDCStatus,QString &workDCStatus,QString &chargeDCStatus);

    bool createSQLiteConnection();
    bool createMSSQLConnection();

    void writeRecordToExcel(QString strTIME);
    void writeOnewRecord(QXlsx::Document &xlsx,int rowCount,int columnCount, QString strTIME,QVariant newIDValue);

private slots:

    void on_btnReset_clicked();

    void on_btnTest_clicked();

    void on_btnQuery_clicked();

    void on_btnExport_clicked();


public:
    QString m_sn;
    QString m_idlecurrent;
    QString m_idlecurrentpf;
    QString m_workcurrent;
    QString m_workcurrentpf;
    QString m_chargecurrent;
    QString m_chargecurrentpf;
    QString m_pf;

    double m_dMinIdleCurrent;
    double m_dMaxIdleCurrent;
    double m_dMinWorkCurrent;
    double m_dMaxWorkCurrent;
    double m_dMinChargeCurrent;
    double m_dMaxChargeCurrent;

private:
    Ui::TestForm *ui;

    QSqlQueryModel  *m_model;

    QWizard *m_wizard;
};

#endif // TESTFORM_H
