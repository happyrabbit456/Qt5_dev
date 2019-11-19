#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>

#include <iostream>
#include <string>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , strLineEdit("")
    , combIndex(1)
    , ui(new Ui::MainWindow)

{
//    string test="111";
//    string ch=" ";
//    test.insert(1,ch);
//    qDebug()<<test.c_str()<<endl;
//    const char *pp=test.c_str();
//    char *ppp=nullptr;
//    ppp=const_cast<char*>(pp);
//    ppp[3]='3';
//    qDebug()<<ppp<<endl;

//    string strTest;
//    cout<<strTest.max_size();

    ui->setupUi(this);

    ui->label->setHidden(true);

    criticalStr="检测扫描码和厂商设置不匹配，确认进行下一次检测吗？";

    m_fontPointSize=20;

    //ui->label->setStyleSheet("color:red;");
    //setStyleSheet("color:#ff6600;");

    //QLabel *label = new QLabel("<h2><i>Hello</i><font color=red>Qt!</font></h2>");

    //    LabelDefaultShow();

    checkTimer=nullptr;

    int index = ui->comboBox->currentIndex();
    qDebug()<<"Index"<< index <<": "<< ui->comboBox->currentText();
    QString currentComboBoxText = ui->comboBox->currentText();
    if(!currentComboBoxText.isNull() && !currentComboBoxText.isEmpty())
    {
        saveFileName=currentComboBoxText;
    }
    qDebug()<<saveFileName;

//    SaveBarScanningCode(QString("111")+QString("\n"));
//    SaveBarScanningCode(QString("222")+QString("\n"));

    char yearChar;
    char monthChar;
    bool ret=GetYearMonthCharacter(yearChar,monthChar);
    if(ret){

    }


    //BDG001BS9K001A093904
    //BD0329BS9K001A195904
//    QString str111="BDG001BS9K001A093904";
    QString str111="BD0329BS9K001A195904";
    ScanningCodeHandle(str111);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LabelShow(const QColor &textColor,const QColor &backgroudColor,
                           int fontPointSize, QString labelText)
{
    ui->label->clear();
    QPalette palette;
    palette.setColor(QPalette::WindowText,textColor);//Qt::blue);//white);
    palette.setColor(QPalette::Background, backgroudColor);//QColor(Qt::white));//(R, G, B));
    ui->label->setAutoFillBackground(true);  //一定要这句，否则不行
    ui->label->setPalette(palette);

    //设置字号
    QFont ft;
    ft.setPointSize(fontPointSize);//20);
    ui->label->setFont(ft);
    ui->label->setText(labelText);//"default");
}

void MainWindow::LabelDefaultShow()
{
    LabelShow(Qt::blue,Qt::white,m_fontPointSize,"default");
}

bool MainWindow::SaveBarScanningCode(QString code)
{
    //如果检测 Pass ，保存扫描码到文件
    if(!saveFileName.isNull() && !saveFileName.isEmpty())
    {
        saveFile.setFileName(saveFileName);
        if(!saveFile.open(QIODevice::ReadWrite|QIODevice::Append|QIODevice::Text))
        {
            QMessageBox::critical(nullptr, tr("错误提示"), tr("打开保存文件失败"), QMessageBox::Yes , QMessageBox::Yes);
            return false;
        }
        else{
            code=code+QString("\n");

            string codeStr=code.toStdString();
            const char* codeString=codeStr.c_str();
            saveFile.write(codeString,qstrlen(codeString));
            saveFile.close();
            return true;
        }
    }
    else
    {
        QMessageBox::critical(nullptr, tr("错误提示"), tr("扫描码保存文件名为空"), QMessageBox::Yes , QMessageBox::Yes);
        return false;
    }

}

void MainWindow::ShowErrorDlg()
{
    //弹框提示
//    int ret = QMessageBox::critical(nullptr, tr("错误提示"), criticalStr, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//    switch (ret) {
//    case QMessageBox::Yes:
//        // Yes was clicked
//        qDebug()<<"Yes was clicked";
//        //                    QTimer::singleShot(1000, this, SLOT(updateWidget()));
//        ui->numlineEdit->setText("");

//        //                    LabelDefaultShow();

//        ui->label->setHidden(true);

//        break;
//    case QMessageBox::No:
//        // No was clicked
//        qDebug()<<"No was clicked";

//        break;
//    default:
//        // should never be reached
//        break;
//    }

    QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical, tr("错误提示"), criticalStr, QMessageBox::Yes | QMessageBox::No);

    msgBox->setAttribute(Qt::WA_DeleteOnClose, true);
    msgBox->button(QMessageBox::Yes)->setText("是");
    msgBox->button(QMessageBox::No)->setText("否");

    // 启动对话框，用res变量记录用户最终点选的按钮
    int res = msgBox->exec();
    if(QMessageBox::Yes == res)
    {
        // Yes was clicked
        qDebug()<<"Yes was clicked";
        //                    QTimer::singleShot(1000, this, SLOT(updateWidget()));
        ui->numlineEdit->setText("");

        //                    LabelDefaultShow();

        ui->label->setHidden(true);
    }
    if(QMessageBox::No == res)
    {
        qDebug()<<"No was clicked";
    }
}

bool MainWindow::GetYearMonthCharacter(char &chYear, char &chMonth)
{
    bool ok=false;
    bool yearCharRet=false;
    bool monthCharRet=false;

    //9代表2019，A代表2020，B代表2021，以此英文字母方式类推，占1位

//    //26
    unsigned char ch='A'; //65
    unsigned char chTest;
    for(unsigned int i=0;i<26;i++)
    {

        chTest=(char)ch+i;
        qDebug()<<"chTest:"<<(char)chTest;
    }

    QDateTime current_date_time =QDateTime::currentDateTime();
//        QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    QString strYear = current_date_time.toString("yyyy");
    qDebug()<<strYear;
    QString strMonth = current_date_time.toString("MM");
    qDebug()<<strMonth;

    if(strYear.compare(QString("2019"))==0)
    {
        chYear='9';
        qDebug()<<chYear;
        yearCharRet = true;
    }
    else
    {
        unsigned int baseYear=2019;

        unsigned int numDecYear = strYear.toUInt(&ok, 10);
        if(ok){
            qDebug() << ok << ":" << numDecYear;//true : 2019

            char chLetter;
            unsigned int temp=numDecYear-baseYear;//25;
            if(temp>=1 && temp <= 25)
            {
                chLetter=(char)ch+temp;
                qDebug()<<"chLetter:"<<(char)chLetter;

                chYear=chLetter;
                qDebug()<<chYear;
                yearCharRet = true;
            }
            else
            {
                //error，超过字母上限
                QMessageBox::critical(nullptr, tr("错误提示"), tr("年份编码超过字母上限"), QMessageBox::Yes , QMessageBox::Yes);
                return false;
            }
        }
    }



    unsigned int baseMonth=1;
    unsigned int numDecMonth = strMonth.toUInt(&ok, 10);
    if(ok){
        qDebug() << ok << ":" << numDecMonth;//true : 11

        char chLetter;
        unsigned int temp=numDecMonth-baseMonth;//12;
        if(temp>=1 && temp <= 12)
        {
            chLetter=(char)ch+temp;
            qDebug()<<"chLetter:"<<(char)chLetter;

            chMonth=chLetter;
            qDebug()<<chMonth;
            monthCharRet = true;
        }
        else
        {
            //error，超过字母上限
            QMessageBox::critical(nullptr, tr("错误提示"), tr("月份编码超过字母上限"), QMessageBox::Yes , QMessageBox::Yes);
            return false;
        }
    }

    if(yearCharRet && monthCharRet)
    {
        return true;
    }
    else{
        return false;
    }
}

bool MainWindow::CheckYearMonthCharacter(char chYear, char chMonth)
{
    bool yearCharRet=false;
    bool monthCharRet=false;

    if(chYear == '9')
    {
        yearCharRet = true;
    }
    else if(chYear >= 'A' && chYear<='Z')
    {
        yearCharRet = true;
    }
    else
    {
        yearCharRet = false;
    }

    if(chMonth>='A'&&chMonth<='L')
    {
        monthCharRet=true;
    }
    else
    {
        monthCharRet=false;
    }

    if(yearCharRet && monthCharRet)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/***
  *判断一个字符串是否为纯数字
  */
bool MainWindow::isDigitStr(QString str)
{
    QByteArray ba = str.toLatin1();//QString 转换为 char*
     const char *temp = ba.data();

//    std::string temp = str.toStdString();
    for (int i = 0; i < str.length(); i++)
    {
        if (temp[i]<'0' || temp[i]>'9')
        {
            return false;
        }
    }

    return true;
}


bool MainWindow::ScanningCodeHandle(QString str)
{
    if(!str.isNull() && !str.isEmpty() && str.length()==20)
    {
        /**/
        str=str.trimmed();

//        char chYear;
//        char chMonth;
//        bool bCharOK = GetYearMonthCharacter(chYear, chMonth);

        bool bYearMonthChar=false;
        QChar yearChar = str.at(8);
        QChar monthChar = str.at(9);
        char yearCh=yearChar.unicode();
        char monthCh=monthChar.unicode();
        bYearMonthChar=CheckYearMonthCharacter(yearCh,monthCh);
        qDebug()<<"yearCh:"<<yearCh<<" "<<"monthCh:"<<monthCh;

        //            1、mid()函数接受两个参数，第一个是起始位置，第二个是取串的长度。如果省略第二个参数，则会从起始位置截取到末尾。正如上面的例子显示的那样

        //            2、函数left()和rigt()类似，都接受一个int类型的参数n，都是对字符串进行截取。不同之处在于，left()函数从左侧截取n个字符，而right()从右侧开始截取。
        //            QString x = "Nine pineapples";
        //            QString y = x.mid(5, 4);            // y == "pine"
        //            QString z = x.mid(5);               // z == "pineapples"
        QString flowCode=str.right(6);
        qDebug()<<"flowCode:"<<flowCode;

        if(combIndex == 0) //Index 0 :  "国光"  20位
        {
//            int pos=str.indexOf("G001");

            QString manufacturerCode=str.mid(2,4);//厂商
            bool bManufacturerCode = (manufacturerCode.compare("G001") == 0) ? true : false;

//            int pos1=str.indexOf("001A");//天健生产 Cube A Speaker Box
//            int pos2=str.indexOf("001B");//天健生产 Cube B Speaker Box
//            int pos3=str.indexOf("002A");//正阳生产 Cube A Speaker Box
//            int pos4=str.indexOf("002B");//正阳生产 Cube B Speaker Box

//            "001A" 天健生产 Cube A Speaker Box
//            "001B" 天健生产 Cube B Speaker Box
//            "002A" 正阳生产 Cube A Speaker Box
//            "002B" 正阳生产 Cube B Speaker Box
            QString supplierCode=str.mid(10,4); //供应商
            bool bSupplierCode=false;
            if(supplierCode.compare("001A")==0 || supplierCode.compare("001B")==0)
            {
                bSupplierCode=true;
            }
            else
            {
                bSupplierCode=false;
            }

            //BDG001BS9K001A093904
            if(str.length()!=20
                    ||!str.startsWith("BD")
                    || !bManufacturerCode
                    || !(str.at(6)=='B' || str.at(6)=='R' )
                    || str.at(7)!='S'
                    || !bYearMonthChar
                    || !bSupplierCode
                    || !isDigitStr(flowCode))
            {
                ui->label->setHidden(false);

                LabelShow(Qt::blue,Qt::red,m_fontPointSize,"Fail");

                //弹框提示
                ShowErrorDlg();

                return false;
            }

        }
        else if(combIndex == 1)   //Index 1 :  "台德" 20位
        {
            //BD0329BS9K001A195906
//            qDebug()<<str.at(6)<<" "<<str.at(7)<<endl;
//            int pos1=str.indexOf("0329");
//            int pos2=str.indexOf("0330");

            QString manufacturerCode=str.mid(2,4);//厂商
            bool bManufacturerCode = false;
            if(manufacturerCode.compare("0329")==0 ||manufacturerCode.compare("0330")==0)
            {
                bManufacturerCode=true;
            }
            else
            {
                bManufacturerCode=false;
            }

            QString supplierCode=str.mid(10,4); //供应商
            bool bSupplierCode=false;
            if((manufacturerCode.compare("0329")==0 && supplierCode.compare("001A")==0) || (manufacturerCode.compare("0330")==0&&supplierCode.compare("001B")==0))
            {
                bSupplierCode=true;
            }
            else
            {
                bSupplierCode=false;
            }

//            int pos3=str.indexOf("001A");//天健生产 Cube A Speaker Box
//            int pos4=str.indexOf("001B");//天健生产 Cube B Speaker Box
            if(str.length()!=20
                    ||!str.startsWith("BD")
                    || !(str.at(6)=='B' || str.at(6)=='R' )
                    || str.at(7)!='S'
                    || !bYearMonthChar
                    || !bManufacturerCode
                    || !bSupplierCode
                    || !isDigitStr(flowCode))// 0330对应001B
            {
                ui->label->setHidden(false);

                LabelShow(Qt::blue,Qt::red,m_fontPointSize,"Fail");

                //弹框提示
                ShowErrorDlg();

                return false;
            }
        }
        else
        {
            return false;
        }


        bool retOK=SaveBarScanningCode(str);
        if(retOK){
            ui->label->setHidden(false);

            LabelShow(Qt::blue,Qt::green,m_fontPointSize,"Pass");

            QTimer::singleShot(1000, this, SLOT(updateWidget()));
        }

        return true;
    }
    else
    {
        ui->label->setHidden(false);

        LabelShow(Qt::blue,Qt::red,m_fontPointSize,"Fail");

        //弹框提示
        ShowErrorDlg();


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

    ui->numlineEdit->clear();
    ui->numlineEdit->setText("");


    ui->numlineEdit->update();
    ui->numlineEdit->repaint();
    ui->numlineEdit->showNormal();
    ui->numlineEdit->resize(ui->numlineEdit->size());
    ui->numlineEdit->adjustSize();

    qApp->processEvents();

    */
}

void MainWindow::check()
{
    QTime checkTime=QTime::currentTime();
    int elapsed = lastTime.msecsTo(checkTime);
    if(elapsed>50) //扫描完成
    {
        QString strScannerCode=ui->numlineEdit->text();
        ScanningCodeHandle(strScannerCode);

        //检查Timer停止
        if(checkTimer!=nullptr){
            checkTimer->stop();
            delete checkTimer;
            checkTimer=nullptr;
            qDebug()<<"checkTimer->stop(); --->>> call done.";
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Return)//16777220)//enter
    {
        qDebug()<<ui->numlineEdit->text();

        strLineEdit=ui->numlineEdit->text();
        bool ret=ScanningCodeHandle(strLineEdit);
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

    QString currentComboBoxText = ui->comboBox->currentText();
    if(!currentComboBoxText.isNull() && !currentComboBoxText.isEmpty())
    {
        saveFileName=currentComboBoxText;
    }
    qDebug()<<saveFileName;

//    SaveBarScanningCode(QString("111")+QString("\n"));
//    SaveBarScanningCode(QString("222")+QString("\n"));
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

}

void MainWindow::on_numlineEdit_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1)
    //        qDebug()<<"on_numlineEdit_textEdited"<<endl;
    //    qDebug()<<arg1;
}

void MainWindow::on_numlineEdit_returnPressed()
{
    //    qDebug()<<"on_numlineEdit_returnPressed"<<endl;
}

void MainWindow::on_numlineEdit_cursorPositionChanged(int arg1, int arg2)
{
    Q_UNUSED(arg1)
    Q_UNUSED(arg2)
}
