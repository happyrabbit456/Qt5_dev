#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QBasicTimer>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>

#include "gpib.h"
#include "currentform.h"
#include "nivisagpib.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef enum enumSelector{
    Selector_Current=0,
    Selector_Voltage,
}SelectorType;

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


    static MainWindow* getMainWindow();
    int getSupportDatabase();

protected:
    void timerEvent(QTimerEvent *event) override;

private slots:
    void on_listViewSelector_clicked(const QModelIndex &index);

private:
    void SetCurrDateTime();

    bool createSQLiteConnection();
    bool createMSSQLConnection();

public:
    CurrentForm *m_pCurrentForm;

    DataBaseEnum m_databaseEnum;

    QSqlDatabase m_dbSQLite;
    QSqlQuery m_querySQLite;
    bool m_bSQLLiteConnection;

    QSqlDatabase m_dbMSSQL;
    QSqlQuery m_queryMSSQL;
    bool m_bMSSQLConnection;

private:
    Ui::MainWindow *ui;

    QBasicTimer m_timer;
};
#endif // MAINWINDOW_H
