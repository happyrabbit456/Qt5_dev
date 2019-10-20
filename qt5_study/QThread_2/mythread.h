#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    //自定义发送的信号
signals:
    void myThreadSignal(const int);
    //自定义槽
public slots:
    void myThreadSlot(const int);
protected:
    void run() override;
};

#endif // MYTHREAD_H
