#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "workerthread.h"
#include <QProgressBar>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 更新进度
    void handleResults(int value)
    {
        qDebug() << "Handle Thread : " << QThread::currentThreadId();
        m_pProgressBar->setValue(value);
    }

    // 开启线程
    void startThread()
    {
        //        WorkerThread *workerThread = new WorkerThread(this);
        //        当多次点击“开始”按钮的时候，就会多次connect()，从而启动多个线程，同时更新进度条
        WorkerThread *workerThread = m_workerThread;
        if(workerThread->isRunning())
        {
            return;
        }

        //connect(workerThread, SIGNAL(resultReady(int)), this, SLOT(handleResults(int)));

        /*
        自动连接：（默认值）如果信号在接收者所依附的线程内发射，则等同于直接连接。
                如果发射信号的线程和接受者所依附的线程不同，则等同于队列连接。
        */
        //        connect(workerThread, SIGNAL(resultReady(int)), this, SLOT(handleResults(int)), Qt::AutoConnection);

        /*
        队列连接：当控制权回到接受者所依附线程的事件循环时，槽函数被调用。槽函数在接收者所依附线程执行。
                也就是说：这种方式既可以在线程内传递消息，也可以跨线程传递消息
        */
        connect(workerThread, SIGNAL(resultReady(int)), this, SLOT(handleResults(int)), Qt::QueuedConnection);

        /*
        与Qt::QueuedConnection类似，但是会阻塞等到关联的slot都被执行。这里出现了阻塞这个词，说明它是专门用来多线程间传递消息的。
        */
        //connect(workerThread, SIGNAL(resultReady(int)), this, SLOT(handleResults(int)), Qt::BlockingQueuedConnection);

        /*
         *
        ASSERT failure in QCoreApplication::sendEvent: "Cannot send events to objects owned by a different thread.
            Current thread 0x0x8100d0. Receiver '' (of type 'MainWindow') was created in thread 0x0x792f10",
            file kernel\qcoreapplication.cpp,
            line 578 15:43:21: 程序异常结束。
        *
        */
        /*
        直接连接：当信号发射时，槽函数将直接被调用。无论槽函数所属对象在哪个线程，槽函数都在发射信号的线程内执行。
        */
        //        connect(workerThread, SIGNAL(resultReady(int)), this, SLOT(handleResults(int)), Qt::DirectConnection);



        // 线程结束后，自动销毁
        connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
        workerThread->start();
    }

    void stopThread()
    {
        // 请求终止
        m_workerThread->requestInterruption();
        m_workerThread->quit();
        m_workerThread->wait();
    }

private:
    QProgressBar *m_pProgressBar;
    WorkerThread *m_workerThread;
};
#endif // MAINWINDOW_H
