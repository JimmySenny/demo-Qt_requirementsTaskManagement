#-------------------------------------------------
#
# Project created by QtCreator 2019-04-26T08:25:15
#
#-------------------------------------------------

QT       += core gui widgets sql

TARGET = RMT
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

#CONFIG += c++11
CONFIG += console c++11

#QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
        main.cpp \
    rmtconf.cpp \
        rmtlogin.cpp \
    rmtmainwindow.cpp \
    rmtmessagebox.cpp \
    singletonuser.cpp \
    dbmysql.cpp

HEADERS += \
    rmtcomm.h \
    rmtconf.h \
        rmtlogin.h \
    rmtmainwindow.h \
    rmtmessagebox.h \
<<<<<<< HEAD
    rmt.h
=======
    rmtsyspara.h \
    singletonuser.h \
    rmtbusipara.h \
    dbmysql.h
>>>>>>> d941d8facdd3209bfd7c19b9dba421f9731fc621

FORMS += \
        rmtlogin.ui \
    rmtmainwindow.ui \
    rmtmessagebox.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#CONFIG += console
