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
    int socketfd_;

public:
    SocketHandler(int socketfd);
    virtual int getData(int numberOfBytes, char *dataBufor);
    virtual int sendData(int numberOfBytes, char *dataBufor);

    int readBytes(int numberOfBytes, char *bufor);
};

#endif // SOCKETHANDLER_HPP
