#include "SecureHandlerNoSecure.hpp"

SecureHandlerNoSecure::SecureHandlerNoSecure(SocketHandler *sc)
    :SecureHandler(sc, 0, 0, 0)
{

}

int SecureHandlerNoSecure::getData(int numberOfBytes, char *dataBufor)
{

}

int SecureHandlerNoSecure::sendData(int numberOfBytes, char *dataBufor)
{

}
