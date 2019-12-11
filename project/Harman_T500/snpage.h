#ifndef SNPAGE_H
#define SNPAGE_H

#include <QObject>
#include <QWidget>
#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>

#include <QMutex>
#include <QTimer>
#include <QTime>

class SNPage : public QWizardPage
{
    Q_OBJECT

public:
    SNPage(QWidget *parent = nullptr);

    bool validatePage() override;
    void resetSNPage();
    void resetAutoScannerTimer();

    bool ScanningCodeHandle(QString strCode);

    bool eventFilter(QObject *obj, QEvent  *event) override;

private:
    void* currentForm;

    QLabel *snLabel;
    QLineEdit *snLineEdit;

    QTime m_lastTime;
    QTime m_currTime;
    QString m_strCurrChangedCode;
    QString m_strLastChangedCode;

    QTimer m_checkAutoScannerTimer;
    bool m_bAutoScan;

    QMutex m_mutexCheckTimer;

public slots:
    void snLineEdit_textChanged(const QString &arg1);
    void CheckAutoScannerHandle();

};

#endif // SNPAGE_H
