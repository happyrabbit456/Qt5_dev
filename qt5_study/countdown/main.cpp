#include "widget.h"

#include <QApplication>

#include <QMetaType>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<Qt::HANDLE>("Qt::HANDLE");

    Widget w;
#ifdef WIN32
    w.resize(400,150);
#endif
    w.show();
    return a.exec();
}
