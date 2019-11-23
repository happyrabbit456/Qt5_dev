#include "showdatabaseform.h"
#include "ui_showdatabaseform.h"

ShowDataBaseForm::ShowDataBaseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowDataBaseForm)
{
    ui->setupUi(this);

    //    TestTableView();
}

ShowDataBaseForm::~ShowDataBaseForm()
{    
    delete ui;
}

void ShowDataBaseForm::testTableView()
{
    QStandardItemModel *model = new QStandardItemModel(0,4);
    ui->tableView->setModel(model);

    //只读
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置选中模式为选中行
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置选中单行
    ui->tableView->setSelectionMode( QAbstractItemView::SingleSelection);


    //添加表头
    model->setHeaderData(0,Qt::Horizontal,"test0");
    model->setHeaderData(1,Qt::Horizontal,"test1");
    model->setHeaderData(2,Qt::Horizontal,"test2");
    model->setHeaderData(3,Qt::Horizontal,"test3");

    int row=0;
    //添加行
    for(;row<4;row++)
    {
        model->insertRows(row,1);

        model->setData(model->index(row,0), QString::number(row)+ "0");
        model->setData(model->index(row,1),QString::number(row)+ "1");
        model->setData(model->index(row,2),QString::number(row)+ "2");
        model->setData(model->index(row,3),QString::number(row)+ "3");

    }

    ui->tableView->show();
}

void ShowDataBaseForm::initializeModel(QSqlTableModel *model)
{
    model->setTable("record");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TIME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("WorkOrder"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Model"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TestStation"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Line"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("OPID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("LineLeader"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("SN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Vendor"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PF"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ErrorCode"));
}


