#include "currentform.h"
#include "ui_currentform.h"

CurrentForm::CurrentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentForm)
{
    ui->setupUi(this);

    initComboGPIB();
}

CurrentForm::~CurrentForm()
{
    delete ui;
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

void CurrentForm::on_comboGPIBSelector_currentIndexChanged(int index)
{
//    qDebug()<<"Current GPIB index changed:"<<index;
    m_niVisaGPIB.m_nCurrGPIBIndex=index;
}
