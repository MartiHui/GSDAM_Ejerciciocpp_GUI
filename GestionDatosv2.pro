#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T13:14:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GestionDatosv2
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
        gui.cpp \
    controller.cpp \
    data.cpp \
    datatemplate.cpp \
    database.cpp \
    interface.cpp \
    dbselector.cpp \
    dbcreator.cpp \
    dimensions.cpp

HEADERS += \
        gui.h \
    controller.h \
    data.h \
    datatemplate.h \
    database.h \
    interface.h \
    m_utilities.h \
    dbselector.h \
    dbcreator.h \
    dimensions.h

FORMS += \
        gui.ui \
    dbselector.ui \
    dbcreator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
