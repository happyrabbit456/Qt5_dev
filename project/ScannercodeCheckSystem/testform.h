#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include <QDebug>
#include <QPlainTextEdit>

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

#include <QMap>

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

private slots:
    void on_btnTest_clicked();

    void on_comboManufacturer_currentIndexChanged(int index);

private:
    Ui::TestForm *ui;

    QPlainTextEdit *m_pPlainTextEditMsg;
    QMap<QString,QString> m_mapTestStatus;
    QMap<int,QString> m_mapManufacturer;
    int m_currManufacturerIndex;
};

#endif // TESTFORM_H
