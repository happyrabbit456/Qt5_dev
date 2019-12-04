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
    currentform.cpp \
    gpib.cpp \
    main.cpp \
    mainwindow.cpp \
    nivisagpib.cpp

HEADERS += \
    currentform.h \
    gpib.h \
    mainwindow.h \
    nivisagpib.h

FORMS += \
    currentform.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += "C:\Program Files (x86)\National Instruments\Shared\ExternalCompilerSupport\C\include"

#QMAKE_LIBDIR += "C:\Program Files (x86)\National Instruments\Shared\ExternalCompilerSupport\C\lib64\msvc"
#LIBS += ni4882.obj

#QMAKE_LIBDIR += "C:\Program Files (x86)\National Instruments\Shared\ExternalCompilerSupport\C\lib64\msvc\ni4882.obj"

#LIBS += -L"C:\Program Files (x86)\National Instruments\Shared\ExternalCompilerSupport\C\lib64\msvc" -lni4882


# 版本信息
VERSION = 1.0.0.0
# 图标
RC_ICONS = logo.ico
# 公司名称
QMAKE_TARGET_COMPANY = "MINAMI Co. Ltd"
# 产品名称
QMAKE_TARGET_PRODUCT = "Harman T500 Current Test"
# 文件说明
QMAKE_TARGET_DESCRIPTION = "Harman T500 Current Test"
# 版权信息
QMAKE_TARGET_COPYRIGHT = "MINAMI Co. Ltd. All rights reserved."
# 中文（简体）
RC_LANG = 0x0004


#win32 {
#    ## Windows common build here
#    !contains(QMAKE_HOST.arch, x86_64) {
#        message("x86 build")
#        ## Windows x86 (32bit) specific build here
#
#        #win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib32/msvc/' -lgpib-32
#        #else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib32/msvc/' -lgpib-32
#
#        win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib32/msvc/' -lni4882
#        else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib32/msvc/' -lni4882
#
#        INCLUDEPATH += 'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib32/msvc'
#        DEPENDPATH += 'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib32/msvc'
#
#        win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib32/msvc/' -lnisyscfg
#        else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib32/msvc/' -lnisyscfg
#
#        INCLUDEPATH += 'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib32/msvc'
#        DEPENDPATH += 'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib32/msvc'
#
#        win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib32/msvc/' -lniSysMon
#        else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib32/msvc/' -lniSysMon
#
#        INCLUDEPATH += 'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib32/msvc'
#        DEPENDPATH += 'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib32/msvc'
#
#    } else {
#        message("x86_64 build")
#        ## Windows x64 (64bit) specific build here
#
#        win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib64/msvc/' -lni4882
#        else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib64/msvc/' -lni4882
#
#        INCLUDEPATH += 'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib64/msvc'
#        DEPENDPATH += 'C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib64/msvc'
#
#    }
#}


win32 {

    QMAKE_CXXFLAGS_EXCEPTIONS_ON = /EHa
    QMAKE_CXXFLAGS_STL_ON = /EHa

    INCLUDEPATH += "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Include"

    ## Windows common build here
    !contains(QMAKE_HOST.arch, x86_64) {
        #message("x86 build")
        ## Windows x86 (32bit) specific build here

        QMAKE_LIBDIR += "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\lib\msc"
        LIBS += visa32.lib

        QMAKE_LIBDIR += "C:\Program Files (x86)\National Instruments\Shared\ExternalCompilerSupport\C\lib32\msvc"
        LIBS += ni4882.obj
    } else {
        #message("x86_64 build")
        ## Windows x64 (64bit) specific build here

        QMAKE_LIBDIR += "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Lib_x64\msc"
        LIBS += visa64.lib nivisa64.lib

        QMAKE_LIBDIR += "C:\Program Files (x86)\National Instruments\Shared\ExternalCompilerSupport\C\lib64\msvc"
        LIBS += ni4882.obj
    }
}

RESOURCES += \
    res.qrc