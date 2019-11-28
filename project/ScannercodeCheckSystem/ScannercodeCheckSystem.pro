QT       += core gui sql axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS DB_SQLite
#DB_SQLite DB_MSSQL

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    showdatabaseform.cpp \
    testform.cpp \
    versionform.cpp

HEADERS += \
    mainwindow.h \
    showdatabaseform.h \
    testform.h \
    versionform.h

FORMS += \
    mainwindow.ui \
    showdatabaseform.ui \
    testform.ui \
    versionform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = logo.ico

RESOURCES += \
    rc.qrc


# 版本信息
VERSION = 1.0.0.0
# 图标
#RC_ICONS = Images/MyApp.ico
# 公司名称
QMAKE_TARGET_COMPANY = "MINAMI Co. Ltd"
# 产品名称
QMAKE_TARGET_PRODUCT = "Baidu BarCode Check"
# 文件说明
QMAKE_TARGET_DESCRIPTION = "Baidu BarCode Check"
# 版权信息
QMAKE_TARGET_COPYRIGHT = "MINAMI Co. Ltd. All rights reserved."
# 中文（简体）
RC_LANG = 0x0004


win32 {
    ## Windows common build here
    !contains(QMAKE_HOST.arch, x86_64) {
        message("x86 build")
        ## Windows x86 (32bit) specific build here

        win32:CONFIG(release, debug|release): LIBS += -LD:/Qt/Qt5.12.5/5.12.5/mingw73_32/lib/ -lQt5AxBase
        else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Qt/Qt5.12.5/5.12.5/mingw73_32/lib/ -lQt5AxBased

        INCLUDEPATH += D:/Qt/Qt5.12.5/5.12.5/mingw73_32/lib
        DEPENDPATH += D:/Qt/Qt5.12.5/5.12.5/mingw73_32/lib

        win32:CONFIG(release, debug|release): LIBS += -LD:/Qt/Qt5.12.5/5.12.5/mingw73_32/lib/ -lQt5AxContainer
        else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Qt/Qt5.12.5/5.12.5/mingw73_32/lib/ -lQt5AxContainerd

        INCLUDEPATH += D:/Qt/Qt5.12.5/5.12.5/mingw73_32/lib
        DEPENDPATH += D:/Qt/Qt5.12.5/5.12.5/mingw73_32/lib
    } else {
        message("x86_64 build")
        ## Windows x64 (64bit) specific build here

        win32:CONFIG(release, debug|release): LIBS += -LD:/Qt/Qt5.12.5/5.12.5/mingw73_64/lib/ -lQt5AxBase
        else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Qt/Qt5.12.5/5.12.5/mingw73_64/lib/ -lQt5AxBased

        INCLUDEPATH += D:/Qt/Qt5.12.5/5.12.5/mingw73_64/include
        DEPENDPATH += D:/Qt/Qt5.12.5/5.12.5/mingw73_64/include

        win32:CONFIG(release, debug|release): LIBS += -LD:/Qt/Qt5.12.5/5.12.5/mingw73_64/lib/ -lQt5AxContainer
        else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Qt/Qt5.12.5/5.12.5/mingw73_64/lib/ -lQt5AxContainerd

        INCLUDEPATH += D:/Qt/Qt5.12.5/5.12.5/mingw73_64/lib
        DEPENDPATH += D:/Qt/Qt5.12.5/5.12.5/mingw73_64/lib
    }
}

#win32 {
#    ## Windows common build here
#    !contains(QMAKE_HOST.arch, x86_64) {
#        message("x86 build")
#        ## Windows x86 (32bit) specific build here
#    } else {
#        message("x86_64 build")
#        ## Windows x64 (64bit) specific build here
#    }
#}

#contains(QT_ARCH, i386) {
#    message("32-bit")
#} else {
#    message("64-bit")
#}






