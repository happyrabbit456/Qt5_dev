#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QCoreApplication>
#include "peony.h"
#include "peonyLover.h"

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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Peony *peony = new Peony();
    peony->setBloomDate(QDateTime::currentDateTime().addSecs(5));

    //one
    PeonyLover * jack = new PeonyLover("Jack");
    QObject::connect(peony, SIGNAL(bloom()), jack, SLOT(onPeonyBloom()));

    //two
    PeonyLover * zhangsan = new PeonyLover("zhang san");
    QObject::connect(peony, SIGNAL(bloom()), zhangsan, SLOT(onPeonyBloom()));

    //three
    QObject::connect(peony, SIGNAL(bloom()), peony, SIGNAL(wizen()));
    QObject::connect(peony, SIGNAL(wizen()), zhangsan, SLOT(onPeonyBloom()));

    return a.exec();
}

