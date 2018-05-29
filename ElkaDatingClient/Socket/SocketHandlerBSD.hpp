#ifndef SOCKETHANDLERBSD_HPP
#define SOCKETHANDLERBSD_HPP
#include "Socket/SocketHandler.hpp"

class SocketHandlerBSD: public SocketHandler
{
    int socketfd_;
public:
    SocketHandlerBSD(int socketfd);
    int getData(int numberOfBytes, char* dataBufor);
    int sendData(int numberOfBytes, char* dataBufor);
};

#endif // SOCKETHANDLERBSD_HPP
