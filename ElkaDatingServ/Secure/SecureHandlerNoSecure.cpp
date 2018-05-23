#include "SecureHandlerNoSecure.hpp"

SecureHandlerNoSecure::SecureHandlerNoSecure(SocketHandler *sc)
    :SecureHandler(sc)
{

}

int SecureHandlerNoSecure::getData(int numberOfBytes, char *dataBufor)
{
    return sc_->getData(numberOfBytes, dataBufor);
}

int SecureHandlerNoSecure::sendData(int numberOfBytes, char *dataBufor)
{
    return sc_->sendData(numberOfBytes, dataBufor);
}
