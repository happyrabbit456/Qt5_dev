#include "mythread.h"
#include <QObject>

MyThread::MyThread(QObject *parent) : QThread(parent)
{
    m_bStopped=false;
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
        // 检测是否停止
        {
            QMutexLocker locker(&m_mutex);
            if (m_bStopped)
            {
                qDebug()<<"m_bStopped true..."<<endl;
                break;
            }
        }
        // locker超出范围并释放互斥锁
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
