#include "parameterform.h"
#include "ui_parameterform.h"
#include "mainwindow.h"
#include "currentform.h"

ParameterForm::ParameterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterForm)
{
    ui->setupUi(this);

    m_settings = new QSettings("settings.ini", QSettings::IniFormat);

    initComboGPIB();

    currentForm=qobject_cast<CurrentForm*>(parent);

    ReadAppSettings();
}

ParameterForm::~ParameterForm()
{
    if(m_settings!=nullptr){
        delete m_settings;
        m_settings=nullptr;
    }

    delete ui;
}

void ParameterForm::on_btnLock_clicked()
{
    WriteAppSettings();

    ui->editMinIdleCurrent->setEnabled(false);
    ui->editMaxIdleCurrent->setEnabled(false);
    ui->editMinWorkCurrent->setEnabled(false);
    ui->editMaxWorkCurrent->setEnabled(false);
    ui->editMinChargeCurrent->setEnabled(false);
    ui->editMaxChargeCurrent->setEnabled(false);
}

void ParameterForm::on_btnUnlock_clicked()
{
    ui->editMinIdleCurrent->setEnabled(true);
    ui->editMaxIdleCurrent->setEnabled(true);
    ui->editMinWorkCurrent->setEnabled(true);
    ui->editMaxWorkCurrent->setEnabled(true);
    ui->editMinChargeCurrent->setEnabled(true);
    ui->editMaxChargeCurrent->setEnabled(true);
}

void ParameterForm::ReadAppSettings()
{
    QString qstr;
    double d;

    CurrentForm* pCurrentForm=static_cast<CurrentForm*>(currentForm);

    d=m_settings->value("MinIdleCurrent",1.000).toDouble();
    pCurrentForm->m_pTestForm->m_dMinIdleCurrent=qAbs(d);//d;
    qstr=QString().sprintf("%5.3f",d);
    ui->editMinIdleCurrent->setText(qstr);

    d=m_settings->value("MaxIdleCurrent",10.000).toDouble();
    pCurrentForm->m_pTestForm->m_dMaxIdleCurrent=qAbs(d);//d;
    qstr=QString().sprintf("%5.3f",d);
    ui->editMaxIdleCurrent->setText(qstr);

    d=m_settings->value("MinWorkCurrent",1.000).toDouble();
    pCurrentForm->m_pTestForm->m_dMinWorkCurrent=qAbs(d);//d;
    qstr=QString().sprintf("%5.3f",d);
    ui->editMinWorkCurrent->setText(qstr);

    d=m_settings->value("MaxWorkCurrent",10.000).toDouble();
    pCurrentForm->m_pTestForm->m_dMaxWorkCurrent=qAbs(d);//d;
    qstr=QString().sprintf("%5.3f",d);
    ui->editMaxWorkCurrent->setText(qstr);

    d=m_settings->value("MinChargeCurrent",1.000).toDouble();
    pCurrentForm->m_pTestForm->m_dMinChargeCurrent=qAbs(d);//d;
    qstr=QString().sprintf("%5.3f",d);
    ui->editMinChargeCurrent->setText(qstr);

    d=m_settings->value("MaxChargeCurrent",10.000).toDouble();
    pCurrentForm->m_pTestForm->m_dMaxChargeCurrent=qAbs(d);//d;
    qstr=QString().sprintf("%5.3f",d);
    ui->editMaxChargeCurrent->setText(qstr);
}

void ParameterForm::WriteAppSettings()
{
    QString qstr;

    CurrentForm* pCurrentForm=static_cast<CurrentForm*>(currentForm);

    qstr=ui->editMinIdleCurrent->text();
    m_settings->setValue("MinIdleCurrent",qstr.toDouble());
    pCurrentForm->m_pTestForm->m_dMinIdleCurrent=qAbs(qstr.toDouble());//qstr.toDouble();

    qstr=ui->editMaxIdleCurrent->text();
    m_settings->setValue("MaxIdleCurrent",qstr.toDouble());
    pCurrentForm->m_pTestForm->m_dMaxIdleCurrent=qAbs(qstr.toDouble());//qstr.toDouble();

    qstr=ui->editMinWorkCurrent->text();
    m_settings->setValue("MinWorkCurrent",qstr.toDouble());
    pCurrentForm->m_pTestForm->m_dMinWorkCurrent=qAbs(qstr.toDouble());//qstr.toDouble();

    qstr=ui->editMaxWorkCurrent->text();
    m_settings->setValue("MaxWorkCurrent",qstr.toDouble());
    pCurrentForm->m_pTestForm->m_dMaxWorkCurrent=qAbs(qstr.toDouble());//qstr.toDouble();

    qstr=ui->editMinChargeCurrent->text();
    m_settings->setValue("MinChargeCurrent",qstr.toDouble());
    pCurrentForm->m_pTestForm->m_dMinChargeCurrent=qAbs(qstr.toDouble());//qstr.toDouble();

    qstr=ui->editMaxChargeCurrent->text();
    m_settings->setValue("MaxChargeCurrent",qstr.toDouble());
    pCurrentForm->m_pTestForm->m_dMaxChargeCurrent=qAbs(qstr.toDouble());//qstr.toDouble();
}

bool ParameterForm::initComboGPIB()
{
    MainWindow *pMainWindow=MainWindow::getMainWindow();


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
    for ( it = pMainWindow->m_niVisaGPIB.m_mapGPIB.begin(); it != pMainWindow->m_niVisaGPIB.m_mapGPIB.end(); ++it ) {
        //用key()和data()分别获取“键”和“值”
        //            qDebug()<<"key:"<<it.key().data()<<" "<<"value:"<<it.value();

        ui->comboGPIBSelector->addItem(it.key().data());
    }
    ui->comboGPIBSelector->setCurrentIndex(pMainWindow->m_niVisaGPIB.m_nCurrGPIBIndex);

    return true;
}

void ParameterForm::on_comboGPIBSelector_currentIndexChanged(int index)
{
    MainWindow *pMainWindow=MainWindow::getMainWindow();
//    qDebug()<<"Current GPIB index changed:"<<index;
    pMainWindow->m_niVisaGPIB.m_nCurrGPIBIndex=index;
}


