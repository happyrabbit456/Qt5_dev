#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
//    void GpibError(const char * msg); /* Error function declaration              */

//    bool DMM_Write(string strWrite);
//    bool DMM_Read(string strWrite, string &strRead);
//    bool DMM_ReadCurrent(double &value);

private slots:
    void on_shutDownCurrentBtn_clicked();

    void on_bootCurrentBtn_clicked();

    void on_chargingCurrentBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
