#include <QCoreApplication>
#include "controller.h"
#include<QDebug>
#include<QThread>

int main(int argc, char *argv[])
{
    qDebug()<<"I am main Thread, my ID:"<<QThread::currentThreadId()<<"\n";

    QCoreApplication a(argc, argv);

    Controller c;

    return a.exec();
}
