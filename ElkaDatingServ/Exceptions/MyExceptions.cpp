#include "MyExceptions.hpp"

const char* MyException::what() const throw()
{
    return "Not specified user error!";
}

const char* CannotOpenFile::what() const throw()
{
    return "Error when try to open file!";
}

const char* DecryptError::what() const throw()
{
    return "Error when try to decrypt data!";
}

const char* EncryptError::what() const throw()
{
    return "Error when try to encrypt data!";
}

const char* CannotOpenPrivatePem::what() const throw()
{
    return "Error when try to open .pem file with private key!";
}

const char* CannotOpenPublicPem::what() const throw()
{
    return "Error when try to open .pem file with public key!";
}

// --------------------------------------------------------

const char* ServerException::what() const throw()
{
    return "Not specified server error!\n";
}

const char* ServerBindError::what() const throw()
{
    return "Error when try to bind server socket!";
}

const char* ServerAcceptError::what() const throw()
{
    return "Error when try to accept new connection!";
}

const char* ServerListenError::what() const throw()
{
    return "Error when try to use listen function!";
}

// --------------------------------------------------------

const char* ClientException::what() const throw()
{
    return "Not specified client error!";
}

const char* ClientInitSemError::what() const throw()
{
    return "Error when try to init client semaphore!";
}

const char* ClientCloseError::what() const throw()
{
    return "Error when try to close client socket!";
}

const char* DBManagerException::what() const throw()
{
    return "Not specified database error!";
}

const char* DBManagerInitError::what() const throw()
{
    return "Error when try to init database connection!";
}

//---------------------------------------------------------------

const char* MessageException::what() const throw()
{
    return "Not specified client error!";
}

const char* NotLoggedInWrongMessageTypeException::what() const throw()
{
    return "User must be logged in to handle this message type.";
}

const char* LoggedInWrongMessageTypeException::what() const throw()
{
    return "User can't be logged in to handle this message type.";
}

