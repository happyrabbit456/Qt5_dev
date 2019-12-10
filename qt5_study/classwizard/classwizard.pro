QT += widgets

HEADERS       = classwizard.h \
    myform.h
SOURCES       = classwizard.cpp \
                main.cpp \
                myform.cpp
RESOURCES     = classwizard.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/dialogs/classwizard
INSTALLS += target

FORMS += \
    myform.ui
