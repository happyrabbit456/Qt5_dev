#include "widget.h"
#include "qDebug2Logcat.h"

#include <QApplication>
#include <QDebug>
#include <QtGlobal>

int main(int argc, char *argv[])
{
    installLogcatMessageHandler("myLogTag");

    QApplication a(argc, argv);
    Widget w;
    w.show();

    qDebug()<<"Hello android 1 ..."<<endl;
    qDebug("Hello android 2 ... \n");

    return a.exec();
}
