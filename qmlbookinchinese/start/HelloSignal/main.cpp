#include <iostream>
#include <string>

using namespace std;

//#include <QGuiApplication>
//#include <QQmlApplicationEngine>


//int main(int argc, char *argv[])
//{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);

//    return app.exec();
//}


//#include <QApplication>
//#include <QPushButton>

//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);

//    QPushButton button("Quit");
//    QObject::connect(&button, &QPushButton::clicked,
//                     &app, &QApplication::quit);
//    button.show();
//    return app.exec();
//}

#include <QCoreApplication>

#include "newspaper.h"
#include "reader.h"

void callback_fun(int times, void (*print)(int len));

void printWelcome(int len)
{
    cout<<"Hello "<<len<<endl;
}

void printGoodbye(int len)
{
    cout<<"Goodbye "<<len<<endl;
}

void callback_fun(int times, void (*print)(int len))
{
    for(int i=0;i<times;i++)
    {
        print(i);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Newspaper newspaper("Newspaper A");
    Reader reader;
    QObject::connect(&newspaper, &Newspaper::newPaper,
                     &reader,    &Reader::receiveNewspaper);
    newspaper.send();

    callback_fun(2,printWelcome);
    callback_fun(2,printGoodbye);

    return app.exec();
}
