#include <QCoreApplication>
#include "mythread.h"
#include "controller.h"

#include <QThread>
#include <Qt>

int main(int argc, char *argv[])
{
    qDebug()<<"I am main Thread, my ID:"<<QThread::currentThreadId()<<"\n";


    QCoreApplication a(argc, argv);

    Controller c;

    return a.exec();
}
