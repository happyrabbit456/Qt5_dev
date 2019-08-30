#include "widget.h"
#include <QApplication>

#include "customwidget.h"
#include "customwidgetv2.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    Widget w;
    //    w.show();

//    QScopedPointer<QWidget> widget(new CustomWidget());
//    widget->resize(240, 120);
//    widget->show();

    QScopedPointer<QWidget> widget(new CustomWidgetV2());
    widget->resize(480, 240);
    widget->show();


    return a.exec();
}
