#ifndef BARSCANNERDLG_H
#define BARSCANNERDLG_H

#include <QDialog>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class BarScannerDlg;
}

class BarScannerDlg : public QDialog
{
    Q_OBJECT

public:
    explicit BarScannerDlg(QWidget *parent = nullptr);
    ~BarScannerDlg();

public:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    Ui::BarScannerDlg *ui;

    QString questionStr;

public:
    QString m_barScannerCode;
};

#endif // BARSCANNERDLG_H
