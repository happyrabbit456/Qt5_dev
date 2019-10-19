#include "widget.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <Qt>



void SecondFirer::onTimeout()
{
    if(m_nSeconds >= 0)
    {
        Qt::HANDLE id = QThread::currentThreadId();
        emit secondLeft(m_nSeconds, id);
        --m_nSeconds;
        qDebug() << "fire secondLeft signal";
    }
    else
    {
        QThread::currentThread()->exit(0);
    }
}

CountThread::CountThread(QWidget *receiver) : m_receiver(receiver)
{
}

CountThread::~CountThread()
{
    qDebug() << "~CountThread";
}

void CountThread::run()
{
    qDebug() << "CountThread id - " << QThread::currentThreadId();
    QTimer timer;
    SecondFirer firer(10);
    connect(&timer, SIGNAL(timeout()), &firer, SLOT(onTimeout()));
    timer.start(1000);

    if(!m_receiver.isNull())
    {
        qDebug() << "connect firer && receiver";
        connect(&firer, SIGNAL(secondLeft(int,Qt::HANDLE)), m_receiver.data(), SLOT(onSecondLeft(int,Qt::HANDLE)));
    }

    exec();
}


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_label(new QLabel)
{
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(m_label);
    setLayout(layout);
    CountThread * t = new CountThread(this);
    connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));
    t->start();
}

Widget::~Widget()
{
}

void Widget::onSecondLeft(int iLeft,  Qt::HANDLE id)
{
    Qt::HANDLE h = QThread::currentThreadId();
    QString str;
    str.sprintf("remain %d, \ncurrent thread id %p, \nfire thread id %p",iLeft,h,id);
    m_label->setText(str);
    if(iLeft == 0)
    {
        QMessageBox::information(this, "CLAP NOW", "It\'s time to clap now!\nClap! Clap! Clap!");
    }
}
