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

    ui->label->setHidden(true);

    criticalStr="检测扫描码和厂商设置不匹配，确认进行下一次检测吗？";

    //ui->label->setStyleSheet("color:red;");
    //setStyleSheet("color:#ff6600;");

    //QLabel *label = new QLabel("<h2><i>Hello</i><font color=red>Qt!</font></h2>");

    //    LabelDefaultShow();

    checkTimer=nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LabelDefaultShow()
{
    ui->label->clear();
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::blue);//white);
    palette.setColor(QPalette::Background, QColor(Qt::white));//(R, G, B));
    ui->label->setAutoFillBackground(true);  //一定要这句，否则不行
    ui->label->setPalette(palette);

    //设置字号
    QFont ft;
    ft.setPointSize(20);
    ui->label->setFont(ft);
    ui->label->setText("default");
}

bool MainWindow::ScanningCodeHandle(QString str)
{
    if(!str.isNull() && !str.isEmpty())
    {
        str=str.trimmed();
        if(combIndex == 0) //Index 0 :  "国光"  31位
        {
            int pos=str.indexOf("P1556");
            if(str.length()!=31 || pos!=11 )
            {
                ui->label->setHidden(false);
                ui->label->clear();
                QPalette palette;
                palette.setColor(QPalette::WindowText,Qt::blue);
                palette.setColor(QPalette::Background, QColor(Qt::red));//(R, G, B));
                ui->label->setAutoFillBackground(true);  //一定要这句，否则不行
                ui->label->setPalette(palette);

                ui->label->setText("Fail");

                //弹框提示
                int ret = QMessageBox::critical(nullptr, "critical", criticalStr, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                switch (ret) {
                case QMessageBox::Yes:
                    // Yes was clicked
                    qDebug()<<"Yes was clicked";
                    //                    QTimer::singleShot(1000, this, SLOT(updateWidget()));
                    ui->numlineEdit->setText("");

                    //                    LabelDefaultShow();

                    ui->label->setHidden(true);

                    break;
                case QMessageBox::No:
                    // No was clicked
                    qDebug()<<"No was clicked";

                    break;
                default:
                    // should never be reached
                    break;
                }

                return false;
            }

        }
        else if(combIndex == 1)   //Index 1 :  "台德" 20位
        {
            qDebug()<<str.at(6)<<" "<<str.at(7)<<endl;
            if(str.length()!=20 ||!str.startsWith("BD") || !(str.at(6)=='B' || str.at(6)=='R' ) || str.at(7)!='S' )
            {
                ui->label->setHidden(false);
                ui->label->clear();
                QPalette palette;
                palette.setColor(QPalette::WindowText,Qt::blue);
                palette.setColor(QPalette::Background, QColor(Qt::red));//(R, G, B));
                ui->label->setAutoFillBackground(true);  //一定要这句，否则不行
                ui->label->setPalette(palette);

                ui->label->setText("Fail");

                //弹框提示
                int ret = QMessageBox::critical(nullptr, "critical", criticalStr, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

                switch (ret) {
                case QMessageBox::Yes:
                    // Yes was clicked
                    qDebug()<<"Yes was clicked";

                    //                    QTimer::singleShot(1000, this, SLOT(updateWidget()));
                    ui->numlineEdit->setText("");

                    //                    LabelDefaultShow();

                    ui->label->setHidden(true);

                    break;
                case QMessageBox::No:
                    // No was clicked
                    qDebug()<<"No was clicked";
                    break;
                default:
                    // should never be reached
                    break;
                }


                return false;
            }
        }
        else
        {
            return false;
        }

        ui->label->setHidden(false);
        ui->label->clear();
        QPalette palette;
        palette.setColor(QPalette::WindowText,Qt::blue);
        palette.setColor(QPalette::Background, QColor(Qt::green));//(R, G, B));
        ui->label->setAutoFillBackground(true);  //一定要这句，否则不行
        ui->label->setPalette(palette);

        ui->label->setText("Pass");

        QTimer::singleShot(1000, this, SLOT(updateWidget()));

        return true;
    }
    else
    {
        return false;
    }
}

//利用时间差来刷新界面
void MainWindow::updateWidget()
{
    ui->numlineEdit->setText("");

    ui->label->setHidden(true);
    /*
    qDebug()<<"updateWidget() done.";
// this->showNormal();

    ui->numlineEdit->clear();
    ui->numlineEdit->setText("");


    ui->numlineEdit->update();
    ui->numlineEdit->repaint();
    ui->numlineEdit->showNormal();
    ui->numlineEdit->resize(ui->numlineEdit->size());
    ui->numlineEdit->adjustSize();

    qApp->processEvents();


    str=ui->numlineEdit->text();
    bool ret=ScanningCodeHandle(str);
    qDebug()<<"ret:"<<ret<<endl;
    if(ret)
    {
        ui->numlineEdit->setText("");




//    ui->numlineEdit->setText("");

    ui->numlineEdit->clear();

        ui->numlineEdit->update();
        ui->numlineEdit->repaint();
        ui->numlineEdit->showNormal();
        ui->numlineEdit->resize(ui->numlineEdit->size());
        ui->numlineEdit->adjustSize();

        qApp->processEvents();

//     qDebug()<<ui->numlineEdit->text();
    }

    */
}

void MainWindow::check()
{
    QTime checkTime=QTime::currentTime();
    int elapsed = lastTime.msecsTo(checkTime);
    if(elapsed>50) //扫描完成
    {
        QString strScannerCode=ui->numlineEdit->text();
        bool ret=ScanningCodeHandle(strScannerCode);

        //检查Timer停止
        checkTimer->stop();
        checkTimer=nullptr;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Return)//16777220)//enter
    {
        qDebug()<<ui->numlineEdit->text();

        str=ui->numlineEdit->text();
        bool ret=ScanningCodeHandle(str);
        if(ret)
        {
            //            ui->numlineEdit->setText("");
        }
    }
}

void MainWindow::on_clearButton_clicked()
{
    qDebug()<<"Done."<<endl;

    ui->numlineEdit->setText("");

    ui->label->setHidden(true);

    //    QTimer::singleShot(1000, this, SLOT(updateWidget()));
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    //将当前索引赋值给变量index，输出当前选项名
    index = ui->comboBox->currentIndex();
    qDebug()<<"Index"<< index <<": "<< ui->comboBox->currentText();

    combIndex=index;
}



/*

void QLineEdit::returnPressed()
This signal is emitted when the Return or Enter key is pressed. Note that if there is a validator() or inputMask() set on the line edit, the returnPressed() signal will only be emitted if the input follows the inputMask() and the validator() returns QValidator::Acceptable.

[slot] void QLineEdit::selectAll()
Selects all the text (i.e. highlights it) and moves the cursor to the end. This is useful when a default value has been inserted because if the user types before clicking on the widget, the selected text will be deleted.

See also setSelection() and deselect().

[signal] void QLineEdit::selectionChanged()
This signal is emitted whenever the selection changes.

See also hasSelectedText() and selectedText().

[signal] void QLineEdit::textChanged(const QString &text)
This signal is emitted whenever the text changes. The text argument is the new text.

Unlike textEdited(), this signal is also emitted when the text is changed programmatically, for example, by calling setText().

Note: Notifier signal for property text.

[signal] void QLineEdit::textEdited(const QString &text)
This signal is emitted whenever the text is edited. The text argument is the new text.

Unlike textChanged(), this signal is not emitted when the text is changed programmatically, for example, by calling setText().

*/

void MainWindow::on_numlineEdit_editingFinished()
{
    //qDebug()<<"on_numlineEdit_editingFinished"<<endl;

    //    qDebug()<<ui->numlineEdit->text();

    //    QTimer::singleShot(1000, this, SLOT(updateWidget()));          //等待一定时间再显示

    /*

    str=ui->numlineEdit->text();
    bool ret=ScanningCodeHandle(str);
    qDebug()<<"ret:"<<ret<<endl;
    if(ret)
    {
//        ui->numlineEdit->setText("");

//        ui->numlineEdit->update();
//        ui->numlineEdit->repaint();
//        ui->numlineEdit->showNormal();
//        ui->numlineEdit->resize(ui->numlineEdit->size());
//        ui->numlineEdit->adjustSize();

//        qApp->processEvents();

        QTimer::singleShot(500, this, SLOT(updateWidget()));          //等待一定时间再显示

//        qDebug()<<ui->numlineEdit->text();
    }

    */
}

void MainWindow::on_numlineEdit_textChanged(const QString &arg1)
{
    //qDebug()<<"on_numlineEdit_textChanged"<<endl;
    qDebug()<<arg1;

    if(arg1.length()==1){
        currTime = QTime::currentTime();
        lastTime = currTime;
//        lastTime = QTime::currentTime();

        currStr=arg1;
        lastStr=arg1;

        checkTimer=new QTimer(this);
        connect(checkTimer, SIGNAL(timeout()), this, SLOT(check()));
        checkTimer->start(50);
    }
    else if(arg1.length()>1){
        currTime = QTime::currentTime();
        int elapsed = lastTime.msecsTo(currTime);
        qDebug()<<"elapsed ="<<elapsed<<"ms";
        lastTime = currTime;


        currStr=arg1;
        int pos=currStr.indexOf(lastStr);
        if(pos==0){
            lastStr=currStr;
            qDebug()<<"the same scanner code";
        }

    }

//    QTime startTime = QTime::currentTime();
//    QThread::msleep(SLEEP_TIME_MILL);
//    QTime stopTime = QTime::currentTime();
//    int elapsed = startTime.msecsTo(stopTime);
//    qDebug()<<"QTime.currentTime ="<<elapsed<<"ms";


    /*
    bool ret=false;
    if(combIndex == 0 && !arg1.isNull() && !arg1.isEmpty() && arg1.length() == 31) //Index 0 :  "国光" 31位
    {
        qDebug()<<"11111 "<<arg1;
        ret=ScanningCodeHandle(arg1);
    }
    if(combIndex == 1 && !arg1.isNull() && !arg1.isEmpty() && arg1.length() == 20) //Index 1 :  "台德"  20位
    {
        qDebug()<<"22222 "<<arg1;
        ret=ScanningCodeHandle(arg1);
    }
    */



}

void MainWindow::on_numlineEdit_textEdited(const QString &arg1)
{
    //        qDebug()<<"on_numlineEdit_textEdited"<<endl;
    //    qDebug()<<arg1;
}

void MainWindow::on_numlineEdit_returnPressed()
{
    //    qDebug()<<"on_numlineEdit_returnPressed"<<endl;
}

void MainWindow::on_numlineEdit_cursorPositionChanged(int arg1, int arg2)
{

}
