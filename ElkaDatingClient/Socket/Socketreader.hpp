#ifndef SOCKETREADER_HPP
#define SOCKETREADER_HPP

#include <iostream>

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

    /**
     * @brief readBytes
     * This function reads data directly from raw socket. Reads as long as it reach the specified number of bytes.
     *
     * @param numberOfBytes
     * Number of bytes to read from socket.
     *
     * @param bufor
     * It is pointer to char table where should be write readed data
     *
     * @return
     * It returns number of read data.
     * If data return value is 0 then connection should be closed!
     */

    int readBytes(int numberOfBytes, char *bufor);
};

#endif // SOCKETREADER_HPP
