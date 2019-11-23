#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString("Manufacturing Test System"));
    w.show();

//    MainWindow *pMainWindow=MainWindow::getMainWindow();
//    MainWindow *pMainWindow=w.getMainWindow();
//    qDebug()<<pMainWindow;

    return a.exec();
}
