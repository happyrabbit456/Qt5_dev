#include "currentform.h"
#include "ui_currentform.h"

#include "mainwindow.h"

CurrentForm::CurrentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentForm)
{
    ui->setupUi(this);

    initComboGPIB();

    resetTestHandle();

    m_settings = new QSettings("settings.ini", QSettings::IniFormat);
    ReadAppSettings();

//    QXlsx::Document xlsx;
//    xlsx.write("A1", "Hello Qt!");
//    xlsx.saveAs("Test.xlsx");

    m_model = new QSqlQueryModel(ui->tableView);
    updateTableView();
}

CurrentForm::~CurrentForm()
{
    if(m_model!=nullptr){
        delete m_model;
        m_model=nullptr;
    }

    if(m_settings!=nullptr){
        delete m_settings;
        m_settings=nullptr;
    }

    delete ui;
}

void CurrentForm::initializeModel(QSqlQueryModel *model)
{
    //数据库数据
    MainWindow* pMainWindow=MainWindow::getMainWindow();
    if(pMainWindow!=nullptr){
        /*
        if(pMainWindow->m_bDBConnection){
            model->setQuery("select * from currentrecord",pMainWindow->m_db);
            if (model->lastError().isValid()){
                qDebug() << model->lastError();
                QMessageBox::warning(this,"warning",model->lastError().text());
            }
        }
        */
        int nSupportDatabase =pMainWindow->getSupportDatabase();
        if(nSupportDatabase==enum_SQLite){
            if(pMainWindow->m_bSQLLiteConnection){
                model->setQuery("select * from currentrecord",pMainWindow->m_dbSQLite);
                if (model->lastError().isValid()){
                    qDebug() << model->lastError();
                    QMessageBox::warning(this,"warning",model->lastError().text());
                }
            }
        }
        else{
            if(pMainWindow->m_bMSSQLConnection){
                model->setQuery("select * from currentrecord",pMainWindow->m_dbMSSQL);
                if (model->lastError().isValid()){
                    qDebug() << model->lastError();
                    QMessageBox::warning(this,"warning",model->lastError().text());
                }
            }
        }
    }




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
//                "idlemincurrent VARCHAR(30),"
//                "idlemaxcurrent  VARCHAR(30),"
//                "workmincurrent VARCHAR(30),"
//                "workmaxcurrent  VARCHAR(30),"
//                "chargemincurrent  VARCHAR(30),"
//                "chargemaxcurrent  VARCHAR(30),"
//                "pf VARCHAR(10),"
//                );




    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("time"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("sn"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("idlecurrent"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("idlecurrentpf"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("workcurrent"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("workcurrentpf"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("chargecurrent"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("chargecurrentpf"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("idlemincurrent"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("idlemaxcurrent"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("workmincurrent"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("workmaxcurrent"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("chargemincurrent"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("chargemaxcurrent"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("pf"));
}

void CurrentForm::updateTableView()
{
    QTableView *tableView=ui->tableView;
    initializeModel(m_model);
    ui->tableView->setModel(m_model);

    //只读
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置选中模式为选中行
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置选中单行
    tableView->setSelectionMode( QAbstractItemView::SingleSelection);

     tableView->setSortingEnabled(false);
     tableView->verticalHeader()->hide();
     tableView->setWordWrap(false);

     tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);//表头居中
     tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);//设置固定宽度

//     // column width
//     tableView->setColumnWidth(0, 60);
//     tableView->setColumnWidth(1, 120);
//     tableView->setColumnWidth(2, 100);
//     tableView->setColumnWidth(3, 80);
//     tableView->setColumnWidth(4, 120);
//     tableView->setColumnWidth(5, 60);
//     tableView->setColumnWidth(6, 60);
//     tableView->setColumnWidth(7, 100);
//     tableView->setColumnWidth(8, 180);
//     tableView->setColumnWidth(9, 60);
//     tableView->setColumnWidth(10, 60);
//     tableView->setColumnWidth(11, 80);

    /*设置tableview等宽*/
//    QHeaderView* headerView = ui->tableWidget->horizontalHeader();
//    headerView->setSectionResizeMode(QHeaderView::Stretch);
    /*或者下面的代码*/
//    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView->resizeColumnsToContents();

     ui->tableView->show();
}

void CurrentForm::ReadAppSettings()
{
    QString qstr;
    double d;

    d=m_settings->value("MinIdleCurrent",1.000).toDouble();
    qstr=QString().sprintf("%5.3f",d);
//    qstr=QString::number(d);
    ui->editMinIdleCurrent->setText(qstr);

    d=m_settings->value("MaxIdleCurrent",10.000).toDouble();
    qstr=QString().sprintf("%5.3f",d);
//    qstr=QString::number(d);
    ui->editMaxIdleCurrent->setText(qstr);

    d=m_settings->value("MinWorkCurrent",1.000).toDouble();
    qstr=QString().sprintf("%5.3f",d);
//    qstr=QString::number(d);
    ui->editMinWorkCurrent->setText(qstr);

    d=m_settings->value("MaxWorkCurrent",10.000).toDouble();
    qstr=QString().sprintf("%5.3f",d);
//    qstr=QString::number(d);
    ui->editMaxWorkCurrent->setText(qstr);

    d=m_settings->value("MinChargeCurrent",1.000).toDouble();
    qstr=QString().sprintf("%5.3f",d);
//    qstr=QString::number(d);
    ui->editMinChargeCurrent->setText(qstr);

    d=m_settings->value("MaxChargeCurrent",10.000).toDouble();
    qstr=QString().sprintf("%5.3f",d);
//    qstr=QString::number(d);
    ui->editMaxChargeCurrent->setText(qstr);
}

void CurrentForm::WriteAppSettings()
{
    QString qstr;

    qstr=ui->editMinIdleCurrent->text();
    m_settings->setValue("MinIdleCurrent",qstr.toDouble());

    qstr=ui->editMaxIdleCurrent->text();
    m_settings->setValue("MaxIdleCurrent",qstr.toDouble());

    qstr=ui->editMinWorkCurrent->text();
    m_settings->setValue("MinWorkCurrent",qstr.toDouble());

    qstr=ui->editMaxWorkCurrent->text();
    m_settings->setValue("MaxWorkCurrent",qstr.toDouble());

    qstr=ui->editMinChargeCurrent->text();
    m_settings->setValue("MinChargeCurrent",qstr.toDouble());

    qstr=ui->editMaxChargeCurrent->text();
    m_settings->setValue("MaxChargeCurrent",qstr.toDouble());
}

void CurrentForm::resetTestHandle()
{
    ui->labelIdleCurrentStatus->setVisible(false);
    ui->labelWorkCurrentStatus->setVisible(false);
    ui->labelChargeCurrentStatus->setVisible(false);
    ui->editIdleCurrent->setText("0.000");
    ui->editWorkCurrent->setText("0.000");
    ui->editChargeCurrent->setText("0.000");
    ui->lineEditSN->setText("");
    ui->lineEditSN->setFocus();
}

bool CurrentForm::initComboGPIB()
{
    ViStatus status;
    status = m_niVisaGPIB.initGPIB();
    if(status == VI_SUCCESS){
        ui->comboGPIBSelector->clear();
//        QFont f;
//        f.setBold(true);
//        f.setPointSize(10);
//        QPalette pa;
//        pa.setColor(QPalette::WindowText,Qt::black);
//        ui->comboGPIBSelector->setPalette(pa);
//        ui->comboGPIBSelector->setFont(f);

        //测试
        //m_niVisaGPIB.m_mapGPIB.insert("GPIB1::22::INSTR",2);

        QMap<string,ViSession>::iterator it; //遍历map
        for ( it = m_niVisaGPIB.m_mapGPIB.begin(); it != m_niVisaGPIB.m_mapGPIB.end(); ++it ) {
            //用key()和data()分别获取“键”和“值”
//            qDebug()<<"key:"<<it.key().data()<<" "<<"value:"<<it.value();

            ui->comboGPIBSelector->addItem(it.key().data());
        }
        ui->comboGPIBSelector->setCurrentIndex(m_niVisaGPIB.m_nCurrGPIBIndex);

        return true;
    }
    else{
        return false;
    }
}

void CurrentForm::updateIdleCurrent(QString qstr)
{
    ui->editIdleCurrent->setText(qstr);
}

void CurrentForm::updateWorkCurrent(QString qstr)
{
    ui->editWorkCurrent->setText(qstr);
}

void CurrentForm::updateChargeCurrent(QString qstr)
{
    ui->editChargeCurrent->setText(qstr);
}

void CurrentForm::on_comboGPIBSelector_currentIndexChanged(int index)
{
//    qDebug()<<"Current GPIB index changed:"<<index;
    m_niVisaGPIB.m_nCurrGPIBIndex=index;
}

void CurrentForm::on_btnReset_clicked()
{
    resetTestHandle();
}

void CurrentForm::on_btnTest_clicked()
{
    wizard.addPage(new SNPage(this));
    wizard.addPage(new IdleCurrentPage(this));
    wizard.addPage(new WorkCurrentPage(this));
    wizard.addPage(new ChargeCurrentPage(this));
    wizard.addPage(new ConclusionPage(this));

    wizard.setWindowTitle("Trivial Wizard");
    wizard.show();
}

void CurrentForm::on_btnLock_clicked()
{
    WriteAppSettings();

    ui->editMinIdleCurrent->setEnabled(false);
    ui->editMaxIdleCurrent->setEnabled(false);
    ui->editMinWorkCurrent->setEnabled(false);
    ui->editMaxWorkCurrent->setEnabled(false);
    ui->editMinChargeCurrent->setEnabled(false);
    ui->editMaxChargeCurrent->setEnabled(false);
}

void CurrentForm::on_btnUnlock_clicked()
{
    ui->editMinIdleCurrent->setEnabled(true);
    ui->editMaxIdleCurrent->setEnabled(true);
    ui->editMinWorkCurrent->setEnabled(true);
    ui->editMaxWorkCurrent->setEnabled(true);
    ui->editMinChargeCurrent->setEnabled(true);
    ui->editMaxChargeCurrent->setEnabled(true);
}
