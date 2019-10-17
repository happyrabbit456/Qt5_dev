#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QtGlobal>
#include <QFile>
#include <QMutex>
#include <QDateTime>
#include <stdio.h>
#include <stdlib.h>


/*
 *
 *
安装之前已定义的消息处理程序，返回一个指向前一个消息处理程序。

消息处理程序是一个函数，用于打印调试信息、警告信息、严重错误和致命的错误的消息。Qt库（debug模式）包含成百上千的警告信息打印，当发生内部错误时（通常是无效的函数参数）。Qt在release模式下构建还包含这些警告，除非在编译时设置QT_NO_WARNING_OUTPUT和/或QT_NO_DEBUG_OUTPUT。如果你实现自己的消息处理程序，就可以完全控制这些消息。

缺省的消息处理程序向标准输出打印消息。如果是一个致命的消息，应用程序就会立即中止。

仅可以定义一个消息处理程序，因为这通常是在应用范围的基础上进行的，以控制调试输出。

调用qInstallMessageHandler(0)可以恢复消息处理程序。
————————————————
版权声明：本文为CSDN博主「一去丶二三里」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/liang19890820/article/details/51838096
*
*
*/

static FILE * g_log_fp = nullptr;
static void closeLogFile()
{
    if(g_log_fp!=nullptr){
        fclose(g_log_fp);
        g_log_fp = nullptr;
    }
}
static void myMessageOutput_file(QtMsgType type,
                                 const QMessageLogContext &context,
                                 const QString &msg)
{
    //加锁 使用QMutex进行加锁、解锁操作，便于我们可以安全的在多线程操作中使用
    static QMutex mutex;
    mutex.lock();

    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(g_log_fp, "Debug: %s (%s:%u, %s)\n",
                localMsg.constData(),
                context.file, context.line,
                context.function);
        break;
    case QtInfoMsg:
        fprintf(g_log_fp, "Info: %s (%s:%u, %s)\n",
                localMsg.constData(),
                context.file,
                context.line,
                context.function);
        break;
    case QtWarningMsg:
        fprintf(g_log_fp, "Warning: %s (%s:%u, %s)\n",
                localMsg.constData(),
                context.file,
                context.line,
                context.function);
        break;
    case QtCriticalMsg:
        fprintf(g_log_fp, "Critical: %s (%s:%u, %s)\n",
                localMsg.constData(),
                context.file,
                context.line,
                context.function);
        break;
    case QtFatalMsg:
        fprintf(g_log_fp, "Fatal: %s (%s:%u, %s)\n",
                localMsg.constData(),
                context.file,
                context.line,
                context.function);
        //break;

        abort();
    }

    // 解锁
    mutex.unlock();
}


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 加锁
    static QMutex mutex;
    mutex.lock();

    QByteArray localMsg = msg.toLocal8Bit();

    QString strMsg("");
    switch(type)
    {
    case QtDebugMsg:
        strMsg = QString("Debug:");
        break;
    case QtInfoMsg:
        strMsg = QString("Info:");
        break;
    case QtWarningMsg:
        strMsg = QString("Warning:");
        break;
    case QtCriticalMsg:
        strMsg = QString("Critical:");
        break;
    case QtFatalMsg:
        strMsg = QString("Fatal:");
        break;
    }

    // 设置输出信息格式
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString strMessage = QString("Message:%1 File:%2  Line:%3  Function:%4  DateTime:%5")
            .arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function).arg(strDateTime);

    // 输出信息至文件中（读写、追加形式）
    QFile file("log.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << strMessage << "\r\n";
    file.flush();
    file.close();

    // 解锁
    mutex.unlock();
}

void myMessageOutput_console(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        //break;

        abort();
    }
}

int main(int argc, char *argv[])
{
    //qInstallMessageHandler 安装消息处理程序
    qInstallMessageHandler(myMessageOutput);

    /*
    static errno_t err_g_log_fp;
    err_g_log_fp = fopen_s(&g_log_fp, "my.log", "wt");
    if(err_g_log_fp != 0){
        qDebug()<<"my.log file open fail."<<endl;

        exit(EXIT_FAILURE);
//        abort();
    }

    //    g_log_fp = fopen("my.log", "wt");

    atexit(closeLogFile);
    qInstallMessageHandler(myMessageOutput_file);
    */

    //    qInstallMessageHandler(myMessageOutput_console);




    QApplication a(argc, argv);


    qDebug()<<"qInstallMessageHandler example."<<endl;

    // 打印信息
    qDebug("This is a debug message.");
    qWarning("This is a warning message.");
    qCritical("This is a critical message.");
    //qFatal("This is a fatal message.");

    MainWindow w;
    w.show();
    return a.exec();
}
