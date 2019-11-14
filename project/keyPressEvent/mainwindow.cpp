#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , str("")
    , combIndex(0)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Return)//16777220)//enter
    {
        //        ui->numlineEdit->setText(event->text());
        //        str.clear();

        qDebug()<<ui->numlineEdit->text();

        str=ui->numlineEdit->text();
        if(!str.isNull() && !str.isEmpty())
        {
            str=str.trimmed();
            if(combIndex == 0) //Index 0 :  "国光"
            {
                int pos=str.indexOf("P1556");
                if(pos!=11)
                {
                    //弹框提示
                    QMessageBox::critical(nullptr, "critical", "111", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                }

            }
            else if(combIndex == 1)   //Index 1 :  "台德"
            {
                qDebug()<<str.at(6)<<" "<<str.at(7)<<endl;
                if(!str.startsWith("BD") || !(str.at(6)=='B' || str.at(6)=='R' ) || str.at(7)!='S' )
                //if(!str.startsWith("BD"))
                {
                    //弹框提示
                    QMessageBox::critical(nullptr, "critical", "222", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                }
            }




            //                        ui->numlineEdit->setText("");
            //            }
            //    else str += event->text();

            //    qDebug()<<ui->numlineEdit->text();
        }
    }
}

void MainWindow::on_clearButton_clicked()
{
    qDebug()<<"Done."<<endl;
    ui->numlineEdit->setText("");
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    //将当前索引赋值给变量index，输出当前选项名
    index = ui->comboBox->currentIndex();
    qDebug()<<"Index"<< index <<": "<< ui->comboBox->currentText();

    combIndex=index;
}
