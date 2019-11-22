#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

/*
class Base
{
public:
    ~Base()
    {
        qDebug()<<"base destructor done.";
    }
};

class Derived : public Base
{
public:
    virtual ~Derived() override //error: '~Derived' marked 'override' but does
                                //        not override any member functions
    {
        qDebug()<<"derived destructor done.";
    }
};
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
