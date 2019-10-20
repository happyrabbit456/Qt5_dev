#include "mythread.h"
#include <QObject>

MyThread::MyThread(QObject *parent) : QThread(parent)
{
}

void MyThread::run()
{
    qDebug()<<"myThread run() start to execute";
    qDebug()<<"     current thread ID:"<<QThread::currentThreadId()<<'\n';
    //循环一百万次
    int count = 0;
    for(int i = 0;i!=1000000;++i)
    {
     ++count;
    }
    // 发送结束信号
    emit myThreadSignal(count);
    exec();
}

void MyThread::myThreadSlot(const int val)
{
    qDebug()<<"myThreadSlot() start to execute";
    qDebug()<<"     current thread ID:"<<QThread::currentThreadId()<<'\n';
    // 循环一百万次
    int count = val;
    for(int i = 0;i!=1000000;++i)
    {
     ++count;
    }
}
