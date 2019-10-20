#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "mythread.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

signals:
    // 发送信号触发线程
    void operate(const int);

public slots:
    // 处理线程执行的结果
    void handleResults(const int rslt)
    {
        qDebug()<<"receive the resultReady signal---------------------------------";
        qDebug()<<"     current thread ID:"<<QThread::currentThreadId()<<'\n';
        qDebug()<<"     the last result is:"<<rslt;
    }
private:
    MyThread *myThrd;
};

#endif // CONTROLLER_H
