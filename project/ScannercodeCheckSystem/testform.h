#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include <QDebug>
#include <QPlainTextEdit>
#include <QTime>
#include <QTimer>
#include <QMap>
#include <QSettings>
#include <QMainWindow>
#include <QMutex>

namespace Ui {
class TestForm;
}

typedef enum enumTestStatus{
    Status_Ready=0,
    Status_Fail,
    Status_Pass,
    Status_Testing,
}TestStatus;

typedef enum enumManufacturer{
    TaiDe=0,
    GuoGuang,
}Manufacturer;

class TestForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestForm(QWidget *parent = nullptr);
    ~TestForm();

private:
    bool ScanningCodeHandle(QString strCode);
    bool UpdateTestStatus(int errorCode,TestStatus status);
    void UpdateTestStatusImage(QString imagePath);
    void InitTestStatusMap();
    void CheckSNExistInDB(int &nErrorCode);
    void resetTestStatus();
    void resetAutoScannerTimer();

public:
    void ReadAppSettings();
    void WriteAppSettings();

protected slots:
    void passStatusDelayHandle();
    void CheckAutoScannerHandle();

private slots:
    void on_btnTest_clicked();

    void on_comboManufacturer_currentIndexChanged(int index);

    void on_lineEditSN_textChanged(const QString &arg1);    

    void on_btnLock_clicked();

    void on_btnUnlock_clicked();

    void on_btnReset_clicked();

private:
    Ui::TestForm *ui;

    QPlainTextEdit *m_pPlainTextEditMsg;
    QMap<int,QString> m_mapTestStatus;
    QMap<int,QString> m_mapManufacturer;
    int m_currManufacturerIndex;

    QTime m_lastTime;
    QTime m_currTime;
    QString m_strCurrChangedCode;
    QString m_strLastChangedCode;

    QTimer *m_checkAutoScannerTimer;
    bool m_bAutoScan;

    QSettings *m_settings;

    QMutex m_mutex;
};

#endif // TESTFORM_H
