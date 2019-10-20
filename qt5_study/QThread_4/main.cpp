#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QString>
#include <QtConcurrent>

void func(QString name)
{
    qDebug() << "Hello" << name << "from" << QThread::currentThread();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFuture<void> fut1 = QtConcurrent::run(func, QString("Thread 1"));
    QFuture<void> fut2 = QtConcurrent::run(func, QString("Thread 2"));

    fut1.waitForFinished();
    fut2.waitForFinished();

    return a.exec();
}
