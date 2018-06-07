#include "SocketHandlerBSD.hpp"


SocketHandlerBSD::SocketHandlerBSD(int socketfd)
    :socketfd_(socketfd)
{}

int SocketHandlerBSD::getData(int numberOfBytes, char *dataBufor)
{
    int index = 0;
    int returnVal;

    while(index != numberOfBytes)
    {
        returnVal = read(socketfd_, (dataBufor+index), numberOfBytes);

        if(returnVal==0)
        {
            return 0;
        }

        else if(returnVal==-1)
        {
            // TODO THROW EXCEPTION
            std::cout<<"READ -1!\n";
            return 0;
        }

        else
        {
            index += returnVal;
        }
    }

    return index;
}

int SocketHandlerBSD::sendData(int numberOfBytes, char *dataBufor)
{
    int index = 0;
    int returnVal;

    while(index != numberOfBytes)
    {
        returnVal = write(socketfd_, (dataBufor+index), numberOfBytes);

        if(returnVal==0)
        {
            return 0;
        }

        else if(returnVal==-1)
        {
            // TODO THROW EXCEPTION
            std::cout<<"READ -1!\n";
            return 0;
        }

        else
        {
            index += returnVal;
        }
    }

    return index;
}
