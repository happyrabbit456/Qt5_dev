#include "mainwindow.h"

#include <QApplication>

/*****************************************************************************
 * Refer to the language interface documentation for details on
 * which header and .obj files to include in your project.
 *****************************************************************************/
#include "ni4882.h"
#include <stdio.h>

#include <QDebug>

#include <iostream>
#include <string>
#include <sstream>

#include <exception>

#include "gpib.h"

using namespace std;

//可以自己定义Exception
class myException: public exception
{
    virtual const char* what() const noexcept
    {
        return "My exception happened";
    }
};

void exceptionSample()
{
    try
    {
        //如果，则抛出异常；
        myException myEx;
        throw myEx;
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }

    try
    {
        cout << "在 try block 中, 准备抛出一个异常." << endl;
        //这里抛出一个异常（其中异常对象的数据类型是int，值为1）
        throw 1;

        //    int* myarray= new int[100000];
    }
    catch (exception& e)
    {
        cout << "Standard exception: " << e.what() << endl;
    }
    catch( int )
    {
        cout<<"int exception"<<endl;
    }

    //注意这里catch语句
    catch(...)
    {
        cout << "在 catch(…) block 中111" << endl;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication a(argc, argv);

    //异常处理实例，pro文件中需要设置
    //QMAKE_CXXFLAGS_EXCEPTIONS_ON = /EHa
    //QMAKE_CXXFLAGS_STL_ON = /EHa

    //exceptionSample();

#ifndef QT_NO_TRANSLATION
    QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator(&a);
    if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        a.installTranslator(translator);
#endif

    MainWindow w;
    w.setWindowTitle(QString::fromLocal8Bit("Harman T500 测试系统"));
    w.show();

//    从Qt 5.10开始，您可以使用单个QApplication属性全局禁用/隐藏/删除Qt对话框“标题栏”上的“?”帮助按钮这些按钮！
//    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);

    return a.exec();
}
