#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QBasicTimer>
#include <QDateTime>
#include <QDebug>

#include "testform.h"
#include "showdatabaseform.h"
#include "versionform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    void SetCurrDateTime();

private:
    Ui::MainWindow *ui;

    TestForm *m_pTestForm;
    ShowDataBaseForm *m_pShowDataForm;
    VersionForm *m_pVersionForm;

    QBasicTimer m_timer;
};
#endif // MAINWINDOW_H
