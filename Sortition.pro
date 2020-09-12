#-------------------------------------------------
#
# Project created by QtCreator 2020-09-07T18:50:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sortition
TEMPLATE = app

QMAKE_TARGET_COMPANY = jkjkil4        #用于指定生产商
QMAKE_TARGET_DESCRIPTION = Sortition    #用于描述应用程序
QMAKE_TARGET_COPYRIGHT = jkjkil4      #用于声明版权
QMAKE_TARGET_PRODUCT = Sortition        #用于指定产品名称

RC_ICONS = A.ico

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
        Class/choosefiledialog.cpp \
        Class/filenamedialog.cpp \
        main.cpp \
        mainwindow.cpp \
        Class/sortitionitemwidget.cpp

HEADERS += \
        Class/choosefiledialog.h \
        Class/filenamedialog.h \
        Class/ignoredmousewidget.h \
        header.h \
        mainwindow.h \
        Class/sortitionitemwidget.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
