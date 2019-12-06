#include "currentform.h"
#include "ui_currentform.h"

CurrentForm::CurrentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentForm)
{
    ui->setupUi(this);

    initComboGPIB();

    resetTestHandle();

    m_settings = new QSettings("settings.ini", QSettings::IniFormat);
    ReadAppSettings();

    QXlsx::Document xlsx;
    xlsx.write("A1", "Hello Qt!");
    xlsx.saveAs("Test.xlsx");
}

CurrentForm::~CurrentForm()
{
    if(m_settings!=nullptr){
        delete m_settings;
        m_settings=nullptr;
    }

    delete ui;
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
