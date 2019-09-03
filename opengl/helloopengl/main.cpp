#include "widget.h"
#include <QApplication>

#include "glwidget.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    GLWidget w;
    w.show();

    return a.exec();
}
