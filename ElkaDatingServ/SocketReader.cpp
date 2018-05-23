#include "SocketReader.hpp"

SocketReader::SocketReader(int socketfd)
    :socketfd_(socketfd)
{}


int SocketReader::readBytes(int numberOfBytes, char *bufor)
{
    int index = 0;
    int returnVal;

    while(index != numberOfBytes)
    {
        returnVal = read(socketfd_, (bufor+index), numberOfBytes);

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
