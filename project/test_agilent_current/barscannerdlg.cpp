#include "barscannerdlg.h"
#include "ui_barscannerdlg.h"

BarScannerDlg::BarScannerDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BarScannerDlg)
{
    ui->setupUi(this);

    questionStr = tr("没有获取到扫描码，退出对话框吗？");
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

    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("退出对话框"),
                                   questionStr,
                                   QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::No) {
        event->ignore();  //忽略退出信号，程序继续运行
    }
    else if (button == QMessageBox::Yes) {
        event->accept();  //接受退出信号，程序退出
    }

}
