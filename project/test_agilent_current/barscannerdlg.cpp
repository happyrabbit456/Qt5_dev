#include "barscannerdlg.h"
#include "ui_barscannerdlg.h"

BarScannerDlg::BarScannerDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BarScannerDlg)
{
    ui->setupUi(this);

    m_questionStr = tr("没有获取到扫描码，退出对话框吗？");
}

BarScannerDlg::~BarScannerDlg()
{
    delete ui;
}

void BarScannerDlg::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return) //enter
    {
        qDebug()<<ui->lineEditScannerCode->text();

        m_barScannerCode=ui->lineEditScannerCode->text();

    }
    if(m_barScannerCode.isNull() || m_barScannerCode.isEmpty())
    {
        //弹框提示
        int ret = QMessageBox::critical(nullptr, tr("critical"), tr("没有获取到扫描码"), QMessageBox::Yes, QMessageBox::Yes);

        switch (ret) {
        case QMessageBox::Yes:
            // Yes was clicked
            qDebug()<<"Yes was clicked";
            break;
        default:
            // should never be reached
            break;
        }
    }
    else{
        close();
    }
}

void BarScannerDlg::closeEvent(QCloseEvent *event)
{
    m_barScannerCode=ui->lineEditScannerCode->text();


    QMessageBox question(QMessageBox::Question, tr("退出对话框"),
                                   m_questionStr,
                                   QMessageBox::Yes | QMessageBox::No);
    // 将原本显示“Yes”的按钮改为显示“是”
    question.setButtonText(QMessageBox::Yes,tr("是"));
    // 将原本显示“No”的按钮改为显示“否”
    question.setButtonText(QMessageBox::No,tr("否"));
//    启动对话框，用res变量记录用户最终点选的按钮
    int res = question.exec();
    if(QMessageBox::Yes == res)
    {
        // Yes was clicked
        qDebug()<<"Yes was clicked";
        event->accept();  //接受退出信号，程序退出
    }
    else if(QMessageBox::No == res)
    {
        qDebug()<<"No was clicked";
        event->ignore();  //忽略退出信号，程序继续运行
    }



//    // 创建一个question弹出对话框，添加两个按钮：Yes和No
//    QMessageBox *msgBox = new QMessageBox(QMessageBox::Question, tr("退出对话框"), m_questionStr, QMessageBox::Yes | QMessageBox::No);

//    msgBox->setAttribute(Qt::WA_DeleteOnClose, true);
//    // 将原本显示“Yes”的按钮改为显示“是”
//    msgBox->setButtonText(QMessageBox::Yes,tr("是"));
//    // 将原本显示“No”的按钮改为显示“否”
//    msgBox->setButtonText(QMessageBox::No,tr("否"));

//    // 启动对话框，用res变量记录用户最终点选的按钮
//    int res = msgBox->exec();
//    if(QMessageBox::Yes == res)
//    {
//        // Yes was clicked
//        qDebug()<<"Yes was clicked";
//        event->accept();  //接受退出信号，程序退出
//    }
//    else if(QMessageBox::No == res)
//    {
//        qDebug()<<"No was clicked";
//        event->ignore();  //忽略退出信号，程序继续运行
//    }
}
