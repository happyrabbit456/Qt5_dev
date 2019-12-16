#ifndef SNDIALOG_H
#define SNDIALOG_H

#include <QDialog>

#include <QLabel>
#include <QLineEdit>

#include <QMutex>
#include <QTimer>
#include <QTime>

#include <QKeyEvent>

namespace Ui {
class SNDialog;
}

class SNDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SNDialog(QWidget *parent = nullptr);
    ~SNDialog() override;

    void resetSNPage();
    void resetAutoScannerTimer();

    bool ScanningCodeHandle(QString strCode);

    bool eventFilter(QObject *obj, QEvent  *event) override;

    void closeEvent(QCloseEvent *event) override;

public slots:
    void CheckAutoScannerHandle();

private slots:
    void on_editDlgSN_textChanged(const QString &arg1);

private:
    Ui::SNDialog *ui;

    QTime m_lastTime;
    QTime m_currTime;
    QString m_strCurrChangedCode;
    QString m_strLastChangedCode;

    QTimer m_checkAutoScannerTimer;
    bool m_bAutoScan;

    QMutex m_mutexCheckTimer;
};

#endif // SNDIALOG_H
