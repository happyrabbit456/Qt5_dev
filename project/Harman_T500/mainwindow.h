#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QBasicTimer>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>

#include "gpib.h"
#include "currentform.h"
#include "nivisagpib.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef enum enumSelector{
    Selector_Current=0,
    Selector_Voltage,
}SelectorType;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

protected:
    void timerEvent(QTimerEvent *event) override;

private slots:
    void on_listViewSelector_clicked(const QModelIndex &index);

private:
    void SetCurrDateTime();

public:
    CurrentForm *m_pCurrentForm;

private:
    Ui::MainWindow *ui;

    QBasicTimer m_timer;
};
#endif // MAINWINDOW_H
