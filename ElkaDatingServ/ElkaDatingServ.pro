QT -= gui
QT += sql

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lssl -lcrypto

SOURCES += \
        main.cpp \
    Client.cpp \
    SingletonClientList.cpp \
    Server.cpp \
    Message.cpp \
    DBManager.cpp \
    MessageHandlerDKPS.cpp \
    SecureHandler.cpp \
    MessageHandler.cpp \
    SocketReader.cpp \
    MyExceptions.cpp \
    Term.cpp \
    Messagehandler.cpp \
    Socketreader.cpp \
    Myexceptions.cpp \
    SocketHandler.cpp \
    SecureHandler.cpp \
    SocketHandlerBSD.cpp \
    SecureHandlerRSA_AES.cpp \
    SecureHandlerAES.cpp \
    SecureHandlerNoSecure.cpp \
    SecureHandlerRSA.cpp


HEADERS += \
    Client.hpp \
    SingletonClientList.hpp \
    Message.hpp \
    Server.hpp \
    DBManager.hpp \
    MessageHandlerDKPS.hpp \
    MessageHandler.hpp \
    MyExceptions.hpp \
    SecureHandler.hpp \
    SocketReader.hpp \
    Term.hpp \
    Messagehandler.hpp \
    Socketreader.hpp \
    Myexceptions.hpp \
    SocketHandler.hpp \
    SecureHandler.hpp \
    SocketHandlerBSD.hpp \
    SecureHandlerRSA_AES.hpp \
    SecureHandlerAES.hpp \
    SecureHandlerNoSecure.hpp \
    SecureHandlerRSA.hpp
