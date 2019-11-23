#ifndef SHOWDATABASEFORM_H
#define SHOWDATABASEFORM_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
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

private:
    void testTableView();
    bool createSQLiteConnection();
    void initializeModel(QSqlTableModel *model);

public:
    QSqlQuery m_query;
    bool m_bSQLiteConnection;

private:
    Ui::ShowDataBaseForm *ui;

    QSqlDatabase m_db;
};

#endif // SHOWDATABASEFORM_H
