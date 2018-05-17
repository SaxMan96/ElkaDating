#include "Myexceptions.hpp"

const char* MyException::what() const throw()
{
    return "No specified user error!";
}

const char* CannotOpenFile::what() const throw()
{
    return "Error when try to open file!";
}

const char* DecryptError::what() const throw()
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
    return "No specified server error!\n";
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
    return "No specified client error!\n";
}

const char* ClientInitSemError::what() const throw()
{
    return "Error when try to init client semaphore!";
}

const char* ClientCloseError::what() const throw()
{
    return "Error when try to close client socket!";
}
