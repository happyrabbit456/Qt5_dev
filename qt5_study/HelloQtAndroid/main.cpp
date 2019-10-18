#include "widget.h"
#include "qDebug2Logcat.h"

#include <QApplication>
#include <QDebug>
#include <QtGlobal>
#include <QLabel>
#include <QPushButton>

int main(int argc, char *argv[])
{
    installLogcatMessageHandler("myLogTag");

    QApplication a(argc, argv);
    Widget w;
    w.show();

    qDebug()<<"Hello android 1 ..."<<endl;
    qDebug("Hello android 2 ... \n");

//    QLabel label("HelloWorld!",&w);
//    label.show();

    QPushButton *button=new QPushButton("Quit",&w);
    QObject::connect(button,SIGNAL(clicked()),&a,SLOT(quit()));
    button->show();

    return a.exec();
}
