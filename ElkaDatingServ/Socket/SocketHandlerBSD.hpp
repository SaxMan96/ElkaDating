#ifndef SOCKETHANDLERBSD_HPP
#define SOCKETHANDLERBSD_HPP


class SocketHandlerBSD
{
    int sockedfd_;
public:
    SocketHandlerBSD();
    int getData(int numberOfBytes, char* dataBufor);
    int sendData(int numberOfBytes, char* dataBufor);
};

#endif // SOCKETHANDLERBSD_HPP
