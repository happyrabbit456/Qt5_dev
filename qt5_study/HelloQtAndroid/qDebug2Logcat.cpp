#if defined(ANDROID)
#include "qDebug2Logcat.h"
#include <android/log.h>
#include <QDebug>
#include <QByteArray>

static const char *g_TAG = nullptr;
static void messageOutput2Logcat(QtMsgType type,
                                 const QMessageLogContext &context,
                                 const QString &msg)
{
    Q_UNUSED(context)

    int prio = ANDROID_LOG_VERBOSE;
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        prio = ANDROID_LOG_DEBUG;
        break;
    case QtInfoMsg:
        prio = ANDROID_LOG_INFO;
        break;
    case QtWarningMsg:
        prio = ANDROID_LOG_WARN;
        break;
    case QtCriticalMsg:
        prio = ANDROID_LOG_INFO;
        break;
    case QtFatalMsg:
        prio = ANDROID_LOG_FATAL;
        abort();
    }
    __android_log_write(prio, g_TAG, localMsg.data());
}

void installLogcatMessageHandler(const char *TAG)
{
    g_TAG = (TAG == nullptr ? "QDebug" : TAG);
    qInstallMessageHandler(messageOutput2Logcat);
}

#endif
