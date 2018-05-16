#ifndef SOCKETREADER_HPP
#define SOCKETREADER_HPP

// unix things
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <unistd.h>

class SocketReader
{
    int socketfd_;

public:
    SocketReader(int socketfd);
    int readBytes(int numberOfBytes, char *bufor);
};

#endif // SOCKETREADER_HPP
