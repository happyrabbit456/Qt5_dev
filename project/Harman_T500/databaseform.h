#ifndef DATABASEFORM_H
#define DATABASEFORM_H

#include <QWidget>
#include <QMessageBox>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include <QtXlsx>
#include "xlsxdocument.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>

namespace Ui {
class DatabaseForm;
}

class DatabaseForm : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseForm(QWidget *parent = nullptr);
    ~DatabaseForm();

protected:
    void initializeModel(QSqlQueryModel *model);

public slots:
    void on_btnQuery_clicked();
    void on_btnExport_clicked();

    void updateTableView();

private:
    Ui::DatabaseForm *ui;

    QSqlQueryModel  *m_model;
};

#endif // DATABASEFORM_H
