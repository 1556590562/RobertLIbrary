l#-------------------------------------------------
#
# Project created by QtCreator 2019-07-15T17:12:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZCSocres
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dialogadds.cpp \
    dialogorgan.cpp \
    dialogcomprehensive.cpp \
    dialogspecialm.cpp \
    maintablewindow.cpp \
    studentinfo.cpp \
    myfunctions.cpp \
    loading.cpp \
    searchdata.cpp

HEADERS += \
        mainwindow.h \
    dialogadds.h \
    dialogorgan.h \
    dialogcomprehensive.h \
    dialogspecialm.h \
    maintablewindow.h \
    studentinfo.h \
    myfunctions.h \
    loading.h \
    searchdata.h

FORMS += \
        mainwindow.ui \
    dialogadds.ui \
    dialogorgan.ui \
    dialogcomprehensive.ui \
    dialogspecialm.ui \
    maintablewindow.ui \
    maintablewindow.ui \
    loading.ui \
    searchdata.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    iamges.qrc

RC_ICONS = cxy.ico
