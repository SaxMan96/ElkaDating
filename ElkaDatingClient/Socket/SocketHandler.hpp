#ifndef SOCKETHANDLER_HPP
#define SOCKETHANDLER_HPP

#include <iostream>

// unix things
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <unistd.h>


class SocketHandler
{
public:
    SocketHandler();
    virtual int getData(int numberOfBytes, char *dataBufor) = 0;
    virtual int sendData(int numberOfBytes, char *dataBufor) = 0;
};

#endif // SOCKETHANDLER_HPP
