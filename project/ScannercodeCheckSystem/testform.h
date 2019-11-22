#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include <QDebug>
#include <QPlainTextEdit>
#include <QTime>
#include <QTimer>
#include <QMap>
#include <QSettings>

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
    bool UpdateTestStatus(QString errorCode,TestStatus status,QString info);
    void UpdateTestStatusImage(QString imagePath);
    void InitTestStatusMap();
    void ReadAppSettings();
    void WriteAppSettings();

private slots:
    void on_btnTest_clicked();

    void on_comboManufacturer_currentIndexChanged(int index);

    void on_lineEditSN_textChanged(const QString &arg1);

    void  CheckAutoScannerHandle();

    void on_btnLock_clicked();

    void on_btnUnlock_clicked();

private:
    Ui::TestForm *ui;

    QPlainTextEdit *m_pPlainTextEditMsg;
    QMap<QString,QString> m_mapTestStatus;
    QMap<int,QString> m_mapManufacturer;
    int m_currManufacturerIndex;

    QTime m_lastTime;
    QTime m_currTime;
    QString m_strCurrChangedCode;
    QString m_strLastChangedCode;

    QTimer *m_checkAutoScannerTimer;
    bool m_bAutoScan;

    QSettings *m_settings;
};

#endif // TESTFORM_H