#ifndef SHOWDATABASEFORM_H
#define SHOWDATABASEFORM_H

#include <QWidget>
#include <QTableView>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class ShowDataBaseForm;
}

class ShowDataBaseForm : public QWidget
{
    Q_OBJECT

public:
    explicit ShowDataBaseForm(QWidget *parent = nullptr);
    ~ShowDataBaseForm();

private slots:
    void on_btnQueryData_clicked();

    void on_btnExport_clicked();

private:
    void testTableView();

    void initializeModel(QSqlQueryModel *model);
    void updateTableView();

    void tableWidgetToExcel(QTableWidget *table,QString title);
    void tableViewToExcel(QTableView *tableView,QString title);

private:
    Ui::ShowDataBaseForm *ui;

    QSqlQueryModel  *m_model;
};

#endif // SHOWDATABASEFORM_H
