#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

/*
Index 0 :  "国光"
Index 1 :  "台德"
*/

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);

private:
    QString str;
    int combIndex;
    QString criticalStr;

protected:
    bool ScanningCodeHandle(QString str);
    void LabelDefaultShow();

protected slots:
    void updateWidget();

private slots:
    void on_clearButton_clicked();


    void on_comboBox_currentIndexChanged(int index);

    void on_numlineEdit_editingFinished();

    void on_numlineEdit_textChanged(const QString &arg1);

    void on_numlineEdit_textEdited(const QString &arg1);

    void on_numlineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
