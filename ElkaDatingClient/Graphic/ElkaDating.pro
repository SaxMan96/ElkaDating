QT -= gui

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
    Package.cpp \
    Exceptions/Myexceptions.cpp \
    Socket/SocketHandler.cpp \
    Socket/SocketHandlerBSD.cpp \
    Secure/SecureHandler.cpp \
    Secure/SecureHandlerAES.cpp \
    Secure/SecureHandlerNoSecure.cpp \
    Secure/SecureHandlerRSA_AES.cpp \
    Secure/SecureHandlerRSA.cpp

HEADERS += \
    Package.hpp \
    Secure/Securehandler.hpp \
    Exceptions/Myexceptions.hpp \
    Socket/SocketHandler.hpp \
    Socket/SocketHandlerBSD.hpp \
    Secure/SecureHandler.hpp \
    Secure/SecureHandlerAES.hpp \
    Secure/SecureHandlerNoSecure.hpp \
    Secure/SecureHandlerRSA_AES.hpp \
    Secure/SecureHandlerRSA.hpp

DISTFILES += \
    crypto/cryptology_init.sh \
    crypto/private_key.pem \
    crypto/public_key.pem \
    crypto/letters.txt \
    crypto/database.sql \
    public_key.pem
