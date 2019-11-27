#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QBasicTimer>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>

#include "testform.h"
#include "showdatabaseform.h"
#include "versionform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef enum enumDataBase{
    enum_SQLite=0,
    enum_MSSQL,
    enum_SQLite_MSSQL,
}DataBaseEnum;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    void SetCurrDateTime();
    bool createSQLiteConnection();
    bool createMSSQLConnection();

public:
    TestForm *m_pTestForm;
    ShowDataBaseForm *m_pShowDataForm;
    VersionForm *m_pVersionForm;

    DataBaseEnum m_databaseEnum;

    QSqlDatabase m_dbSQLite;
    QSqlQuery m_querySQLite;
    bool m_bSQLLiteConnection;

    QSqlDatabase m_dbMSSQL;
    QSqlQuery m_queryMSSQL;
    bool m_bMSSQLConnection;


public:
//    MainWindow* getMainWindow();
    static MainWindow* getMainWindow();

    void closeEvent(QCloseEvent *event) override;

    int getSupportDatabase();
private:
    Ui::MainWindow *ui;    

    QBasicTimer m_timer;
};
#endif // MAINWINDOW_H
