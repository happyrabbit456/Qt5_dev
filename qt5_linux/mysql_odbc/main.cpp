#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include <QtSql/QSqlDatabase>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); //database driver
    db.setHostName("localhost");//127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("mysql");
    db.setUserName("cai");
    db.setPassword("happyrabbit123");
    if (!db.open())
        qDebug()<<"can't open!";
    else
        qDebug()<<"open!";
//    ————————————————
//            版权声明：本文为CSDN博主「飞翔的蚯蚓」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
//            原文链接：https://blog.csdn.net/qq_37105120/article/details/84000341


        return a.exec();
}
