#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QThread>
#include <QPointer>

class SecondFirer : public QObject
{
    Q_OBJECT
public:
    SecondFirer(int seconds) : m_nSeconds(seconds){}

signals:
    void secondLeft(int sec, Qt::HANDLE id);

public slots:
    void onTimeout();
private:
    int m_nSeconds;
};

class CountThread : public QThread
{
public:
    CountThread(QWidget * receiver);
    ~CountThread();

protected:
    void run();

private:
    QPointer<QWidget> m_receiver;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void onSecondLeft(int sec, Qt::HANDLE id);


private:
    QLabel * m_label;
};

#endif // WIDGET_H
