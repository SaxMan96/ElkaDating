#-------------------------------------------------
#
# Project created by QtCreator 2018-04-20T17:05:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TIN_mkI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
LIBS += -lssl -lcrypto

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    signindialog.cpp \
    signupdialog.cpp \
    datingmain.cpp \
    Exceptions/Myexceptions.cpp \
    Secure/SecureHandler.cpp \
    Secure/SecureHandlerAES.cpp \
    Secure/SecureHandlerNoSecure.cpp \
    Secure/SecureHandlerRSA.cpp \
    Secure/SecureHandlerRSA_AES.cpp \
    Socket/SocketHandler.cpp \
    Socket/SocketHandlerBSD.cpp \
    Package.cpp \
    WeekView.cpp \
    MainView.cpp

HEADERS += \
    signindialog.h \
    signupdialog.h \
    datingmain.h \
    Exceptions/Myexceptions.hpp \
    Secure/SecureHandler.hpp \
    Secure/SecureHandlerAES.hpp \
    Secure/SecureHandlerNoSecure.hpp \
    Secure/SecureHandlerRSA.hpp \
    Secure/SecureHandlerRSA_AES.hpp \
    Socket/SocketHandler.hpp \
    Socket/SocketHandlerBSD.hpp \
    Package.hpp \
    WeekView.h \
    MainView.h

FORMS += \
    signindialog.ui \
    signupdialog.ui \
    datingmain.ui \
    dialog.ui \
    WeekView.ui \
    MainView.ui

SUBDIRS += \
    ElkaDating.pro

DISTFILES += \
    letters.txt \
    test/WeekViewGrid.qml
