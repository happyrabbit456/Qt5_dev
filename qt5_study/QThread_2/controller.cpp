
#include "controller.h"
#include "mythread.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    myThrd = new MyThread;
    connect(myThrd,&MyThread::myThreadSignal,this,&Controller::handleResults);
    // 该线程结束时销毁
    connect(myThrd, &QThread::finished, this, &QObject::deleteLater);
    connect(this,&Controller::operate,myThrd,&MyThread::myThreadSlot);
    // 启动该线程
    myThrd->start();
    QThread::sleep(5);
    emit operate(999);
}

Controller::~Controller()
{
    myThrd->stop();
    myThrd->quit();
    myThrd->wait();
}

