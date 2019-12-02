QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



win32 {
    INCLUDEPATH += "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Include"

    QMAKE_CXXFLAGS_EXCEPTIONS_ON = /EHa
    QMAKE_CXXFLAGS_STL_ON = /EHa

    ## Windows common build here
    !contains(QMAKE_HOST.arch, x86_64) {
        #message("x86 build")
        ## Windows x86 (32bit) specific build here

        QMAKE_LIBDIR += "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\lib\msc"
        LIBS += visa32.lib
    } else {
        #message("x86_64 build")
        ## Windows x64 (64bit) specific build here

        QMAKE_LIBDIR += "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Lib_x64\msc"
        LIBS += visa64.lib nivisa64.lib
    }
}
