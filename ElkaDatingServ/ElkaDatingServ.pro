QT -= gui
QT += core sql
QT += core
QT += widgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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

SOURCES += main.cpp \
    DB/DBManager.cpp \
    Exceptions/MyExceptions.cpp \
    MessageHandler/MessageHandler.cpp \
    Secure/SecureHandler.cpp \
    Secure/SecureHandlerAES.cpp \
    Secure/SecureHandlerNoSecure.cpp \
    Secure/SecureHandlerRSA.cpp \
    Secure/SecureHandlerRSA_AES.cpp \
    Socket/SocketHandler.cpp \
    Socket/SocketHandlerBSD.cpp \
    Client.cpp \
    Message.cpp \
    Server.cpp \
    SingletonClientList.cpp \
    SocketReader.cpp \
    Term.cpp \
    MessageContent/MessageContent.cpp \
    MessageContent/LoginMessageContent.cpp \
    MessageContent/RegistrationMessageContent.cpp \
    MessageContent/SendMultipleMessageContent.cpp \
    Event.cpp \
    MessageContent/AddTermPrefMessageContent.cpp \
    MessageContent/EditTermPrefMessageContent.cpp

HEADERS += \
    DB/DBManager.hpp \
    Exceptions/MyExceptions.hpp \
    MessageHandler/MessageHandler.hpp \
    Secure/SecureHandler.hpp \
    Secure/SecureHandlerAES.hpp \
    Secure/SecureHandlerNoSecure.hpp \
    Secure/SecureHandlerRSA.hpp \
    Secure/SecureHandlerRSA_AES.hpp \
    Socket/SocketHandler.hpp \
    Socket/SocketHandlerBSD.hpp \
    Client.hpp \
    Message.hpp \
    Server.hpp \
    SingletonClientList.hpp \
    SocketReader.hpp \
    Term.hpp \
    MessageContent/MessageContent.hpp \
    MessageContent/LoginMessageContent.hpp \
    MessageContent/RegistrationMessageContent.hpp \
    MessageContent/SendMultipleMessageContent.hpp \
    Event.hpp \
    MessageContent/AddTermPrefMessageContent.hpp \
    MessageContent/EditTermPrefMessageContent.hpp

DISTFILES += \
    ../database.sql
