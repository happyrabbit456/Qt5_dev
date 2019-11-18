#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QThread>
#include <QFile>

/*
Index 0 :  "国光"  20位
Index 1 :  "台德"  20位
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
    QString strLineEdit;
    int combIndex;
    QString criticalStr;

    int m_fontPointSize;

    QTime currTime;
    QTime lastTime;
    QTime timerTime;
    QString currStr;
    QString lastStr;

    QTimer *checkTimer;

    QFile saveFile;
    QString saveFileName;

protected:
    bool ScanningCodeHandle(QString str);
    void LabelShow(const QColor &textColor,const QColor &backgroudColor,
                               int fontPointSize,QString labelText);
    void LabelDefaultShow();
    bool SaveBarScanningCode(QString code);
    void ShowErrorDlg();

    bool GetYearMonthCharacter(char &chYear, char &chMonth);
    bool CheckYearMonthCharacter(char chYear, char chMonth);
protected slots:
    void updateWidget();
    void check();

private slots:
    void on_clearButton_clicked();


    void on_comboBox_currentIndexChanged(int index);

    void on_numlineEdit_editingFinished();

    void on_numlineEdit_textChanged(const QString &arg1);

    void on_numlineEdit_textEdited(const QString &arg1);

    void on_numlineEdit_returnPressed();

    void on_numlineEdit_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
