#include "SocketHandler.hpp"


SocketHandler::SocketHandler(int socketfd)
    :socketfd_(socketfd)
{}

int SocketHandler::getData(int numberOfBytes, char *dataBufor)
{

}

int SocketHandler::sendData(int numberOfBytes, char *dataBufor)
{

}

int SocketHandler::readBytes(int numberOfBytes, char *bufor)
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
