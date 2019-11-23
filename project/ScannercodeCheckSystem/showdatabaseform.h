#ifndef SHOWDATABASEFORM_H
#define SHOWDATABASEFORM_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>


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
    Ui::ShowDataBaseForm *ui;
};

#endif // SHOWDATABASEFORM_H
