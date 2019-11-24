#include "showdatabaseform.h"
#include "ui_showdatabaseform.h"

#include <QTableWidget>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QAxObject>
#include <ActiveQt/QAxObject>

ShowDataBaseForm::ShowDataBaseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowDataBaseForm)
{
    ui->setupUi(this);

    //    TestTableView();

    m_model=new QSqlTableModel(this);


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

    //只读
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置选中模式为选中行
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置选中单行
    ui->tableView->setSelectionMode( QAbstractItemView::SingleSelection);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TIME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("WorkOrder"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Model"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TestStation"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Line"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("OPID"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("LineLeader"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("SN"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Vendor"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("PF"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("ErrorCode"));
}



void ShowDataBaseForm::on_btnQueryData_clicked()
{
    testTableView();
    //    ui->tableView->setModel(m_model);

    //    //只读
    //    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //    //设置选中模式为选中行
    //    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //    //设置选中单行
    //    ui->tableView->setSelectionMode( QAbstractItemView::SingleSelection);

    //    initializeModel(m_model);
    //    ui->tableView->setModel(m_model);
    //    ui->tableView->resizeColumnsToContents();

    //    ui->tableView->show();
}

void ShowDataBaseForm::on_btnExport_clicked()
{
    tableViewToExcel(ui->tableView,"111");
}

//第一个参数是页面上的表格，第二个是导出文件的表头数据
void ShowDataBaseForm::tableWidgetToExcel(QTableWidget *table,QString title)
{
    QString fileName = QFileDialog::getSaveFileName(table, "保存",QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),"Excel 文件(*.xls *.xlsx)");
    if (fileName!="")
    {
        QAxObject *excel = new QAxObject;
        if (excel->setControl("Excel.Application")) //连接Excel控件
        {
            excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
            excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
            QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
            workbooks->dynamicCall("Add");//新建一个工作簿
            QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
            QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

            int i,j;
            //QTablewidget 获取数据的列数
            int colcount=table->columnCount();
            //QTablewidget 获取数据的行数
            int rowscount=table->rowCount();

             QAxObject *cell,*col;
            //标题行
            cell=worksheet->querySubObject("Cells(int,int)", 1, 1);
            cell->dynamicCall("SetValue(const QString&)", title);
            cell->querySubObject("Font")->setProperty("Size", 18);
            //调整行高
            worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
            //合并标题行
            QString cellTitle;
            cellTitle.append("A1:");
            cellTitle.append(QChar(colcount - 1 + 'A'));
            cellTitle.append(QString::number(1));
            QAxObject *range = worksheet->querySubObject("Range(const QString&)", cellTitle);
            range->setProperty("WrapText", true);
            range->setProperty("MergeCells", true);
            range->setProperty("HorizontalAlignment", -4108);//xlCenter
            range->setProperty("VerticalAlignment", -4108);//xlCenter
            //列标题
            for(i=0;i<colcount;i++)
            {
                QString columnName;
                columnName.append(QChar(i  + 'A'));
                columnName.append(":");
                columnName.append(QChar(i + 'A'));
                col = worksheet->querySubObject("Columns(const QString&)", columnName);
                col->setProperty("ColumnWidth", table->columnWidth(i)/6);
                cell=worksheet->querySubObject("Cells(int,int)", 2, i+1);
                //QTableWidget 获取表格头部文字信息
                columnName=table->horizontalHeaderItem(i)->text();

                cell->dynamicCall("SetValue(const QString&)", columnName);
                cell->querySubObject("Font")->setProperty("Bold", true);
                cell->querySubObject("Interior")->setProperty("Color",QColor(191, 191, 191));
                cell->setProperty("HorizontalAlignment", -4108);//xlCenter
                cell->setProperty("VerticalAlignment", -4108);//xlCenter
            }

            //数据区

            //QTableWidget 获取表格数据部分
            for(i=0;i<rowscount;i++){
                for (j=0;j<colcount;j++)
                {
                    worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", table->item(i,j)?table->item(i,j)->text():"");
                }
            }

            //画框线
            QString lrange;
            lrange.append("A2:");
            lrange.append(colcount - 1 + 'A');
            lrange.append(QString::number(table->rowCount() + 2));
            range = worksheet->querySubObject("Range(const QString&)", lrange);
            range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
            range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));
            //调整数据区行高
            QString rowsName;
            rowsName.append("2:");
            rowsName.append(QString::number(table->rowCount() + 2));
            range = worksheet->querySubObject("Range(const QString&)", rowsName);
            range->setProperty("RowHeight", 20);
            workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(fileName));//保存至fileName
            workbook->dynamicCall("Close()");//关闭工作簿
            excel->dynamicCall("Quit()");//关闭excel
            delete excel;
            excel=nullptr;
            if (QMessageBox::question(nullptr,"完成","文件已经导出，是否现在打开？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
            {
                QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
            }
        }
        else
        {
            QMessageBox::warning(nullptr,"错误","未能创建 Excel 对象，请安装 Microsoft Excel。",QMessageBox::Apply);
        }
    }
}

//第一个参数是页面上的表格，第二个是导出文件的表头数据
void ShowDataBaseForm::tableViewToExcel(QTableView *tableView,QString title)
{
    QString fileName = QFileDialog::getSaveFileName(this, "保存",QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),"Excel 文件(*.xls *.xlsx)");
    if (fileName!="")
    {
        QAxObject *excel = new QAxObject;
        if (excel->setControl("Excel.Application")) //连接Excel控件
        {
            excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
            excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
            QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
            workbooks->dynamicCall("Add");//新建一个工作簿
            QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
            QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

            int i,j;

            //QTableView 获取列数
            int colcount=tableView->model()->columnCount();// tableView->model->columnCount();
            //QTableView 获取行数
            int rowcount=tableView->model()->rowCount();// tableView->model->rowCount();

            QAxObject *cell,*col;
            QAxObject *range;

            /**/
            //标题行
            cell=worksheet->querySubObject("Cells(int,int)", 1, 1);

            cell->dynamicCall("SetValue(const QString&)", title);

            cell->querySubObject("Font")->setProperty("Size", 18);
            //调整行高
            worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
            //合并标题行
            QString cellTitle;
            cellTitle.append("A1:");
            cellTitle.append(QChar(colcount - 1 + 'A'));
            cellTitle.append(QString::number(1));
            range = worksheet->querySubObject("Range(const QString&)", cellTitle);
            range->setProperty("WrapText", true);
            range->setProperty("MergeCells", true);
            range->setProperty("HorizontalAlignment", -4108);//xlCenter
            range->setProperty("VerticalAlignment", -4108);//xlCenter
            //列标题
            for(i=0;i<colcount;i++)
            {
                QString columnName;
                columnName.append(QChar(i  + 'A'));
                columnName.append(":");
                columnName.append(QChar(i + 'A'));
                col = worksheet->querySubObject("Columns(const QString&)", columnName);
                col->setProperty("ColumnWidth", tableView->columnWidth(i)/6);
                cell=worksheet->querySubObject("Cells(int,int)", 2, i+1);

                //QTableView 获取表格头部文字信息
                columnName=tableView->model()->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString();
                cell->dynamicCall("SetValue(const QString&)", columnName);
                cell->querySubObject("Font")->setProperty("Bold", true);
                cell->querySubObject("Interior")->setProperty("Color",QColor(191, 191, 191));
                cell->setProperty("HorizontalAlignment", -4108);//xlCenter
                cell->setProperty("VerticalAlignment", -4108);//xlCenter
            }

            //数据区 QTableView 获取表格数据部分
            for(i=0;i<rowcount;i++) //行数
            {
                for (j=0;j<colcount;j++)   //列数
                {
                    QModelIndex index = tableView->model()->index(i, j);
                    QString strdata=tableView->model()->data(index).toString();
                    worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", strdata);
                }
            }

            //画框线
            QString lrange;
            lrange.append("A2:");
            lrange.append(colcount - 1 + 'A');
            lrange.append(QString::number(tableView->model()->rowCount() + 2));
            range = worksheet->querySubObject("Range(const QString&)", lrange);
            range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
            range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));
            //调整数据区行高
            QString rowsName;
            rowsName.append("2:");
            rowsName.append(QString::number(tableView->model()->rowCount()));//table->rowCount() + 2));
            range = worksheet->querySubObject("Range(const QString&)", rowsName);
            range->setProperty("RowHeight", 20);
            workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(fileName));//保存至fileName
            workbook->dynamicCall("Close()");//关闭工作簿
            excel->dynamicCall("Quit()");//关闭excel
            delete excel;
            excel=nullptr;
            if (QMessageBox::question(nullptr,"完成","文件已经导出，是否现在打开？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
            {
                QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
            }
        }
        else
        {
            QMessageBox::warning(nullptr,"错误","未能创建 Excel 对象，请安装 Microsoft Excel。",QMessageBox::Apply);
        }
    }
}
