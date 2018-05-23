#ifndef SOCKETHANDLER_HPP
#define SOCKETHANDLER_HPP


class SocketHandler
{
public:
    virtual int getData(int numberOfBytes, char *dataBufor);
    virtual int sendData(int numberOfBytes, char *dataBufor);
    SocketHandler();
};

#endif // SOCKETHANDLER_HPP
