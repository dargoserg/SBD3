#-------------------------------------------------
#
# Project created by QtCreator 2020-01-14T14:53:56
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SBD_V3_1
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
        mcdatastore.cpp \
        myclassaddressinput.cpp \
        myclassautorizacion.cpp \
        myclassdiagnosisselection.cpp \
        myclasslocationofdiagnosisselection.cpp \
        myclassreportcreator.cpp \
        myclasssslclient.cpp \
        myclasstablemodel.cpp

HEADERS += \
        mainwindow.h \
        mcdatastore.h \
        myclassaddressinput.h \
        myclassautorizacion.h \
        myclassdiagnosisselection.h \
        myclasslocationofdiagnosisselection.h \
        myclassreportcreator.h \
        myclasssslclient.h \
        myclasstablemodel.h \
        struct.h

FORMS += \
        mainwindow.ui \
        myclassaddressinput.ui \
        myclassautorizacion.ui \
        myclassdiagnosisselection.ui \
        myclasslocationofdiagnosisselection.ui \
        myclassreportcreator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
